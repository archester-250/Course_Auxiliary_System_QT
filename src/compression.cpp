#include "compression.h"
compression::compression(/* args */)
{
}

compression::~compression()
{
}
bool compression::Code(string inRoad, string outRoad)
{
    FILE * fpin = fopen(inRoad.c_str(),"r");
    if(fpin == NULL)
    {
        printf("ERROR--invalid input road\n");
        return false;
    }

    FILE * fpout = fopen(outRoad.c_str(), "wb");
    if(fpout == NULL)
    {
        printf("ERROR--invalid output filename\n");
        fclose(fpin);
        return false;
    }
    HuffmanTree ht;
    for(int i = 0; i < 2 * N; i++)
    {
        ht[i].lc = 0;
        ht[i].rc = 0;
        ht[i].parent = 0;
        ht[i].weight = 0;
    }
    long fileLength = 0;
    int c = fgetc(fpin);
    while(c != EOF)
    {
        ht[c + 1].weight++;
        // printf("%d\n",c);
        c = fgetc(fpin);
    }//统计字符个数
    CreateHT(ht);
    char ** HC = (char **)malloc((N + 1) * sizeof(char *));
    char * cd = (char *)malloc((N) * sizeof(char));
    memset(cd, 0, N);
    HuffmanCoding(HC, cd, ht);//哈夫曼编码
    free(cd);
    // PrintCodeList(HC);
    for(int i = 1; i <= N; i++)
    {
        fileLength += (ht[i].weight * strlen(HC[i]));//计算文件长度
    }
    fwrite(&fileLength, sizeof(long), 1, fpout);//存在二进制文件中
    // for(int i = 1; i <= 128; i++)
    // {
    //     printf("%d\n", ht[i].parent);
    // }
    for(int i = 2 * N - 1; i > N; i--)
    {
        // fputc(i, fpout);
        fputc(ht[i].lc, fpout);
        fputc(ht[i].rc, fpout);
    }//存左右子树
    // for(int i = 1; i <= 128; i++)
    // {
    //     printf("%d\n", ht[i].parent);
    // }
    fseek(fpin, 0, SEEK_SET);//将文件指针返回到头部
    c = fgetc(fpin);
    char buf[8] = {0};
    int index = 0;
    while(c != EOF)//遍历整个文件，将其转移到二进制文件中
    {
        int length = strlen(HC[c + 1]);
        for(int i = 0; i < length; i++)
        {
            buf[index++] = HC[c + 1][i];
            if(index == 8)
            {
                int num = 0;
                for(int i = 0; i < 8; i++)
                {
                    num *= 2;
                    if(buf[i] == '1')
                    {
                        num++;
                    }
                }
                fputc(num, fpout);
                index = 0;
            }
        }
        c = fgetc(fpin);
    }
    int num = 0;
    for(int i = 0; i < 8; i++)
    {
        num *= 2;
        if(buf[i] == '1')
        {
            num++;
        }
    }
    fputc(num, fpout);
    for(int i = 1; i <= N; i++)
    {
        free(HC[i]);
    }
    free(HC);
    fclose(fpin);
    fclose(fpout);
    return true;
}
void compression::CreateHT(HuffmanTree ht)
{
    int maxweight = 0;
    for(int i = 1; i <= N; i++)
    {
        maxweight += ht[i].weight;
    }
    ht[0].weight = maxweight;
    for(int i = N + 1; i < 2 * N; i++)//将N + 1到2N - 1的下标的左右子树填充
    {
        int min1 = 0, min2 = min1;
        for(int j = 1; j < i; j++)
        {
            if(ht[j].parent == 0)
            {
                if(ht[j].weight <= ht[min1].weight)
                {
                    min2 = min1;
                    min1 = j;
                }
                else if(ht[j].weight <= ht[min2].weight)
                {
                    min2 = j;
                }
            }
        }
        ht[min1].parent = i;
        ht[min2].parent = i;
        ht[i].weight = ht[min1].weight + ht[min2].weight;
        ht[i].lc = min1;
        ht[i].rc = min2;
    }
}
void compression::HuffmanCoding(char ** HC, char * cd, HuffmanTree ht)
{
    for(int i = 1; i <= N; i++)
    {
        int start = N - 1;
        for(int current = i, next = ht[i].parent; next != 0; current = next, next = ht[next].parent)
        {
            if(ht[next].lc == current) cd[--start] = '0';
            else cd[--start] = '1';
        }
        HC[i] = (char *)malloc((N - start) * sizeof(char));
        strcpy(HC[i], &cd[start]);
    }
}
void compression::PrintCodeList(char ** HC)
{
    for(int i = 1; i <= N; i++)
    {
        printf("%d : %s\n", i - 1, HC[i]);
    }
}
bool compression::Decode(string inRoad, string outRoad)
{
    FILE * fpin = fopen(inRoad.c_str(), "rb");
    if(fpin == NULL)
    {
        printf("ERROR--invalid input filename\n");
        return false;
    }

    FILE * fpout = fopen(outRoad.c_str(), "w");
    if(fpout == NULL)
    {
        printf("ERROR--invalid output filename\n");
        fclose(fpin);
        return false;
    }
    long fileLength;
    fread(&fileLength, sizeof(long), 1, fpin);
    int lc,rc;
    TREENODE tempTree[N - 1];
    //0->255,1->254
    for(int i = 0; i < N - 1; i++)
    {
        lc = fgetc(fpin);
        rc = fgetc(fpin);
        // printf("%d %d\n", lc, rc);
        tempTree[i].lc = lc;
        tempTree[i].rc = rc;
    }
    char * cd = (char *)malloc(N * sizeof(char));
    memset(cd, 0, N);
    char ** de_HC = (char **)malloc((N + 1) * sizeof(char *));
    // for(int i = 1; i <= N; i++)
    // {
    //     de_HC[i] = (char *)malloc(N * sizeof(char));
    //     memset(de_HC[i], 0, N);
    // }
    Build_Tree(tempTree, de_HC, cd, 0, 0);
    // PrintCodeList(de_HC);
    char buf_1[128] = {0};
    char buf_2[8] = {0};
    int index = 0;
    int c = fgetc(fpin);
    while(c != EOF)//逐字符读入
    {
        for(int i = 7; i >= 0; i--)
        {
            buf_2[i] = (c % 2) + '0';
            c /= 2;
        }
        if(fileLength >= 8)//剩余文件长度大于等于8
        {
            fileLength -= 8;
            for(int i = 0; i < 8; i++)//逐条01读入
            {
                buf_1[index++] = buf_2[i];
                int count = 0, temp_index;
                for(int j = 1; j <= N && count <= 1; j++)
                {
                    if(memcmp(buf_1, de_HC[j], index) == 0)
                    {
                        count++;
                        temp_index = j;
                    }
                }
                if(count == 1)//刚好有一个相符
                {
                    fputc(temp_index - 1, fpout);
                    memset(buf_1, 0, index);
                    index = 0;
                }
            }
        }
        else
        {
            for(int i = 0; i < fileLength; i++)//与上部分只有这里不同
            {
                buf_1[index++] = buf_2[i];
                int count = 0, temp_index;
                for(int j = 1; j <= N && count <= 1; j++)
                {
                    if(memcmp(buf_1, de_HC[j], index) == 0)
                    {
                        count++;
                        temp_index = j;
                    }
                }
                if(count == 1)
                {
                    fputc(temp_index - 1, fpout);
                    memset(buf_1, 0, index);
                    index = 0;
                }
            }
        }
        c = fgetc(fpin);
    }
    free(cd);
    for(int i = 1; i <= N; i++)
    {
        free(de_HC[i]);
    }
    free(de_HC);
    fclose(fpin);
    fclose(fpout);
    return true;
}
void compression::Build_Tree(TREENODE * tempTree, char ** de_HC, char * cd, int depth, int index)//递归建立
{
    if(tempTree[index].lc <= 128)//走的是左子且左子为叶子
    {
        cd[depth] = '0';//填充最后一位编码
        int length = strlen(cd);
        de_HC[tempTree[index].lc] = (char *)malloc((length + 1) * sizeof(char));
        memset(de_HC[tempTree[index].lc], 0, length + 1);
        strcpy(de_HC[tempTree[index].lc], cd);
        cd[depth] = 0;//还原，以防意外
    }
    else
    {
        cd[depth] = '0';//置为0
        Build_Tree(tempTree, de_HC, cd, depth + 1, 255 - tempTree[index].lc);//递归调用，注意左右子树编号与其存储结构下标的差异
        cd[depth] = 0;
    }
    if(tempTree[index].rc <= 128)//右子树同理
    {
        cd[depth] = '1';
        int length = strlen(cd);
        de_HC[tempTree[index].rc] = (char *)malloc((length + 1) * sizeof(char));
        memset(de_HC[tempTree[index].rc], 0, length + 1);
        strcpy(de_HC[tempTree[index].rc], cd);
        cd[depth] = 0;
    }
    else
    {
        cd[depth] = '1';
        Build_Tree(tempTree, de_HC, cd, depth + 1, 255 - tempTree[index].rc);
        cd[depth] = 0;
    }
}
void compression::BM(char * target, char * pattern, int * pos, int &inx, int posindex)
{
    int * badChar = (int *)malloc(N * sizeof(int));//记录模式串中每个字符最后出现的位置
    GenerateBadChar(pattern, badChar);//预处理模式串，填充suffix，prefix
    int plen = strlen(pattern);
    int tlen = strlen(target);
    int * suffix = (int *)malloc(plen * sizeof(int));
    int * prefix = (int *)malloc(plen * sizeof(int));
    GenerateGoodSuffix(pattern, suffix, prefix);
    int i = 0, j, moveLen1, moveLen2;//j表示主串与模式串匹配的第一个字符
    while(i < tlen - plen + 1)
    {
        for(j = plen - 1; j >= 0 && target[i + j] == pattern[j]; --j); //模式串从后往前匹配
        if(j < 0)//匹配成功
        {
            pos[inx++] = i + posindex;//主串与模式串第一个匹配的字符的全局位置
            i++;
        }
        else
        {
            moveLen1 = j - badChar[target[i + j]];
            moveLen2 = 0;
            if(j < plen - 1)//如果有好后缀的话
            {
                moveLen2 = MoveByGoodSuffix(j, plen, suffix, prefix);//按照好后缀规则移动距离
            }
            if(moveLen1 > moveLen2) i += moveLen1;
            else i += moveLen2;//取大的移动
        }
        
    }
    free(badChar);
    free(suffix);
    free(prefix);
}
void compression::GenerateBadChar(char * pattern, int * badChar)
{
    for(int i = 0; i < N; i++)
    {
        badChar[i] = -1;
    }
    for(int i = 0; i < strlen(pattern); i++)
    {
        badChar[pattern[i]] = i;
    }
}
void compression::GenerateGoodSuffix(char * pattern, int * suffix, int * prefix)
{
    int plen = strlen(pattern);
    for(int i = 0; i < plen; i++)//两个数组初始化
    {
        suffix[i] = -1;
        prefix[i] = 0;
    }
    for(int i = 0; i < plen - 1; i++)
    {
        int j = i;
        int k = 0;
        while(j >= 0 && pattern[j] == pattern[plen - 1 - k])
        {
            --j;
            ++k;
            suffix[k] = j + 1;
        }
        if(j == -1) prefix[k] = 1;
    }
}
int compression::MoveByGoodSuffix(int badIndex, int plen, int * suffix, int * prefix)
{
    int goodSuffixLen = plen - badIndex - 1;
    if(suffix[goodSuffixLen] != -1)//case1，找到跟好后缀一样的模式子串（多个的话，存的靠后的那个（子串起始下标））
    {
        return badIndex - suffix[goodSuffixLen] + 1;
    }
    for(int r = badIndex + 2; r < plen; ++r)
    {
        if(prefix[plen - r]) return r;//m-r是好后缀的子串的长度，如果这个好后缀的子串是模式串的前缀子串，在上面没有找到相同的好后缀下，移动r位，对齐前缀到好后缀
    }
    return plen;//case3,都没有匹配的，移动m位（模式串长度）
}
void compression::SearchOrigin()
{
    char inputRoad[FILENAME_MAX + 10] = {0};
    printf("Please input the road of INPUT filename you want to search (no more than 260 characters): ");
    char input = getchar();
    int count = 0;
    while(input == '\n')
    {
        printf("You put nothing...\n");
        printf("Please input the road of INPUT filename you want to search (no more than 260 characters): ");
        input = getchar();
    }
    while((input != '\n') && count <= 260)
    {
        inputRoad[count++] = input;
        input = getchar();
    }
    if(count == 261)
    {
        while(getchar() != '\n');
        printf("You're a bad guy...I've saved the former 260 characters to keep security\n");
    }

    FILE * fpin = fopen(inputRoad, "r");
    if(fpin == NULL)
    {
        printf("ERROR--invalid input filename\n");
        return;
    }
    char buf[257] = {0};
    char str[55] = {0};
    printf("Please input the word you want to search, no more than 50 words, press enter to end : ");
    input = getchar();
    count = 0;
    while(input == '\n')
    {
        printf("You put nothing...\n");
        input = getchar();
    }
    while((input != '\n') && count <= 50)
    {
        str[count++] = input;
        input = getchar();
    }
    if(count == 51)
    {
        while(getchar() != '\n');
        printf("You're a bad guy...I've saved the former 50 characters to keep security\n");
    }
    int pos[51000] = {0};
    int index = 256, posindex = 0,i = 0;
    int temp, prei;
    while((temp = fread(&buf[256 - index], sizeof(char), index, fpin)) == index)//一次读入256位
    {
        // int result;
        // while((result = BM(&buf[index], str)) != -1)
        // {
        //     index += result;
        //     pos[i++] = posindex + index;
        //     index += strlen(str);
        // }
        index = 256 - (strlen(str) - 1);
        BM(buf, str, pos, i, posindex);
        posindex += index;
        strcpy(buf, &buf[index]);//将可能与后方匹配段的字符串移到开头
    }
    buf[temp + 1] = 0;
    BM(buf, str, pos, i, posindex);
    printf("Search result : \nThe key word has occured %d times;\nThe start positions are : \n", i);
    for(int j = 0; j < i; j++)
    {
        printf("%d\t", pos[j]);
    }
    printf("\n");
    fclose(fpin);
}
void compression::SearchBinary()
{
    char inputRoad[FILENAME_MAX + 10] = {0};
    printf("Please input the road of INPUT filename you want to search (no more than 260 characters): ");
    char input = getchar();
    int count = 0;
    while(input == '\n')
    {
        printf("You put nothing...\n");
        printf("Please input the road of INPUT filename you want to search (no more than 260 characters): ");
        input = getchar();
    }
    while((input != '\n') && count <= 260)
    {
        inputRoad[count++] = input;
        input = getchar();
    }
    if(count == 261)
    {
        while(getchar() != '\n');
        printf("You're a bad guy...I've saved the former 260 characters to keep security\n");
    }
    while(!judge_wxl(inputRoad))
    {
        printf("The suffix must be \".wxl\" format >_<\n");
        printf("Please input the road of input filename you want to search (no more than 260 characters): ");
        input = getchar();
        count = 0;
        while(input == '\n')
        {
            printf("You put nothing...\n");
            printf("Please input the filename you want to search (no more than 260 characters): ");
            input = getchar();
        }
        while((input != '\n') && count <= 260)
        {
            inputRoad[count++] = input;
            input = getchar();
        }
        if(count == 261)
        {
            while(getchar() != '\n');
            printf("You're a bad guy...I've saved the former 260 characters to keep security\n");
        }
    }

    FILE * fpin = fopen(inputRoad, "rb");
    if(fpin == NULL)
    {
        printf("ERROR--invalid input filename\n");
        return;
    }
    int buf;
    char str[55] = {0};
    printf("Please input the word you want to search, no more than 50 words, press enter to end : ");
    input = getchar();
    count = 0;
    while(input == '\n')
    {
        printf("You put nothing...");
        input = getchar();
    }
    while((input != '\n') && count <= 50)
    {
        str[count++] = input;
        input = getchar();
    }
    if(count == 51)
    {
        while(getchar() != '\n');
        printf("You're a bad guy...I've saved the former 50 characters to keep security");
    }

    long fileLength;
    fread(&fileLength, sizeof(long), 1, fpin);
    int * startpos = (int *)malloc(fileLength * sizeof(int));
    GenerateStartpos(startpos, inputRoad);
    // for(int i = 0; i < 1000; i++)
    // {
    //     printf("%d\t", startpos[i]);
    // }
    // printf("\n");

    int lc,rc;
    TREENODE tempTree[N - 1];
    //0->255,1->254
    for(int i = 0; i < N - 1; i++)
    {
        lc = fgetc(fpin);
        rc = fgetc(fpin);
        tempTree[i].lc = lc;
        tempTree[i].rc = rc;
    }
    char * cd = (char *)malloc(N * sizeof(char));
    memset(cd, 0, N);
    char ** de_HC = (char **)malloc((N + 1) * sizeof(char *));
    Build_Tree(tempTree, de_HC, cd, 0, 0);
    free(cd);

    char strbi[50 * N + 1] = {0};
    for(int i = 0; i < strlen(str); i++)
    {
        strcpy(&strbi[strlen(strbi)], de_HC[str[i] + 1]);
    }
    
    int pos[51000] = {0};
    char bufbi[256 * 8 + 1] = {0};
    char buf_8[8] = {0};
    int prei;
    int length = 0, i = 0, index = 0;
    int floatflag = 0;
    buf = fgetc(fpin);
    while(buf != EOF)//逐字符读入
    {
        for(int j = 7; j >= 0; j--)
        {
            buf_8[j] = buf % 2 + '0';
            buf /= 2;
        }
        if(fileLength >= 8)//大于等于8的情况
        {
            fileLength -= 8;
            for(int j = 0; j < 8; j++)
            {
                bufbi[index] = buf_8[j];
                prei = i;
                ARGS args;
                args.pos = pos;
                args.length = length;
                args.startpos = startpos;
                BM_SearchBinary(bufbi, strbi, args, i, index, floatflag);
                if(prei == i)//没有匹配到字符
                {
                    index = strlen(bufbi);
                }
                else//匹配到了
                {
                    strcpy(bufbi, &bufbi[++index]);
                    index = strlen(bufbi);
                    memset(&bufbi[index], 0, 256 * 8 - index);
                }
                if(strlen(bufbi) == 256 * 8)//如果bufbi爆满，则清空
                {
                    index = strlen(strbi);
                    strcpy(bufbi, &bufbi[256 * 8 - index]);
                    memset(&bufbi[index], 0, 256 * 8 - index);
                }
                length++;
            }
        }
        else
        {
            for(int j = 0; j < fileLength; j++)
            {
                bufbi[index] = buf_8[j];
                prei = i;
                ARGS args;
                args.pos = pos;
                args.length = length;
                args.startpos = startpos;
                BM_SearchBinary(bufbi, strbi, args, i, index, floatflag);
                if(prei == i)
                {
                    index = strlen(bufbi);
                }
                else
                {
                    strcpy(bufbi, &bufbi[++index]);
                    index = strlen(bufbi);
                    memset(&bufbi[index], 0, 256 * 8 - index);
                }
                if(strlen(bufbi) == 256 * 8)
                {
                    index = strlen(strbi);
                    strcpy(bufbi, &bufbi[256 * 8 - index]);
                    memset(&bufbi[index], 0, 256 * 8 - index);
                }
                length++;
            }
        }
        buf = fgetc(fpin);
    }
    printf("Search result : \nThe key word has occured %d times;\nThe start positions are : \n", i);
    for(int j = 0; j < i; j++)
    {
        printf("%d\t", pos[j] - strlen(str));
    }
    printf("\n");
    fclose(fpin);
}
void compression::BM_SearchBinary(char * target, char * pattern, ARGS args, int &inx,int &index, int &floatflag)
{//BM二进制版本
    if(strlen(pattern) > strlen(target)) return;
    int * badChar = (int *)malloc(N * sizeof(int));
    GenerateBadChar(pattern, badChar);
    int plen = strlen(pattern);
    int tlen = strlen(target);
    int * suffix = (int *)malloc(plen * sizeof(int));
    int * prefix = (int *)malloc(plen * sizeof(int));
    GenerateGoodSuffix(pattern, suffix, prefix);
    int i = 0, j, moveLen1, moveLen2;
    while(i < tlen - plen + 1)
    {
        for(j = plen - 1; j >= 0 && target[i + j] == pattern[j]; --j);
        if(j < 0)
        {
            while(args.startpos[floatflag++] <= args.length);
            args.pos[inx++] = --floatflag;
            index = i;
            i++;
        }
        else
        {
            moveLen1 = j - badChar[target[i + j]];
            moveLen2 = 0;
            if(j < plen - 1)
            {
                moveLen2 = MoveByGoodSuffix(j, plen, suffix, prefix);
            }
            if(moveLen1 > moveLen2) i += moveLen1;
            else i += moveLen2;
        }
        
    }
    free(badChar);
    free(suffix);
    free(prefix);
}
void compression::GenerateStartpos(int * startpos, char * filename)//与解码的算法相似，只不过在匹配成功之后改为了输入到startpos数组
{
    FILE * fpin = fopen(filename, "rb");
    long fileLength;
    fread(&fileLength, sizeof(long), 1, fpin);
    int lc,rc;
    TREENODE tempTree[N - 1];
    //0->255,1->254
    for(int i = 0; i < N - 1; i++)
    {
        lc = fgetc(fpin);
        rc = fgetc(fpin);
        // printf("%d %d\n", lc, rc);
        tempTree[i].lc = lc;
        tempTree[i].rc = rc;
    }
    char * cd = (char *)malloc(N * sizeof(char));
    memset(cd, 0, N);
    char ** de_HC = (char **)malloc((N + 1) * sizeof(char *));
    // for(int i = 1; i <= N; i++)
    // {
    //     de_HC[i] = (char *)malloc(N * sizeof(char));
    //     memset(de_HC[i], 0, N);
    // }
    Build_Tree(tempTree, de_HC, cd, 0, 0);
    // PrintCodeList(de_HC);
    char buf_1[128] = {0};
    char buf_2[8];
    int index = 0;
    int c = fgetc(fpin);
    int start = 0, startinx = 0;
    while(c != EOF)
    {
        for(int i = 7; i >= 0; i--)
        {
            buf_2[i] = (c % 2) + '0';
            c /= 2;
        }
        if(fileLength >= 8)
        {
            fileLength -= 8;
            for(int i = 0; i < 8; i++)
            {
                buf_1[index++] = buf_2[i];
                int count = 0, temp_index;
                for(int j = 1; j <= N && count <= 1; j++)
                {
                    if(memcmp(buf_1, de_HC[j], index) == 0)
                    {
                        count++;
                        temp_index = j;
                    }
                }
                if(count == 1)
                {
                    startpos[startinx++] = start - strlen(de_HC[temp_index]) + 1;
                    memset(buf_1, 0, index);
                    index = 0;
                }
                start++;
            }
        }
        else
        {
            for(int i = 0; i < fileLength; i++)
            {
                buf_1[index++] = buf_2[i];
                int count = 0, temp_index;
                for(int j = 1; j <= N && count <= 1; j++)
                {
                    if(memcmp(buf_1, de_HC[j], index) == 0)
                    {
                        count++;
                        temp_index = j;
                    }
                }
                if(count == 1)
                {
                    startpos[startinx++] = start;
                    memset(buf_1, 0, index);
                    index = 0;
                }
                start++;
            }
        }
        c = fgetc(fpin);
    }
    free(cd);
    for(int i = 1; i <= N; i++)
    {
        free(de_HC[i]);
    }
    free(de_HC);
    fclose(fpin);
}
int compression::judge_wxl(char * str)//检测.wxl后缀
{
    int length = strlen(str);
    if(str[length - 1] == 'l' && str[length - 2] == 'x' && str[length - 3] == 'w' && str[length - 4] == '.')
    {
        return 1;
    }
    return 0;
}