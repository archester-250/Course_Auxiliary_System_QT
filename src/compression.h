/**
 * @file compression.h
 * @author your name (you@domain.com)
 * @brief 压缩算法实现
 * @version 0.1
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "utils.h"
#define N 128//128个可转成字符的数字
typedef int WeightType;//权重的类型
using namespace std;
/**
 * @brief huffman树存储单元
 * 
 */
typedef struct
{
    WeightType weight;
    int parent, lc, rc;
}HTNODE;
/**
 * @brief 存储后N - 1个树的左右孩子的存储单元
 * 
 */
typedef struct
{
    int lc, rc;
}TREENODE;
/**
 * @brief 参数的结构体
 * 
 */
typedef struct
{
    int * pos;
    int length;
    int * startpos;
}ARGS;
typedef HTNODE HuffmanTree[2 * N];//huffman树的存储空间
class compression
{
private:
    /* data */
public:
    compression(/* args */);
    ~compression();
    /**
     * @brief 编码的总执行函数
     * 
     */
    bool Code(string inRoad, string outRoad);
    /**
     * @brief 创建一颗哈夫曼树
     * 
     * @param ht 已经初始化的哈夫曼树
     */
    void CreateHT(HuffmanTree ht);
    /**
     * @brief 哈夫曼编码创建码表
     * 
     * @param HC 码表二维动态数组
     * @param cd 辅助数组
     * @param ht 已经构建的哈夫曼树
     */
    void HuffmanCoding(char ** HC, char * cd, HuffmanTree ht);
    /**
     * @brief 打印码表（测试用）
     * 
     * @param HC 码表
     */
    void PrintCodeList(char ** HC);
    /**
     * @brief 解码的总执行函数
     * 
     */
    bool Decode(string inRoad, string outRoad);
    /**
     * @brief 递归创建哈夫曼树
     * 
     * @param tempTree 存储解码后的左右子树信息
     * @param de_HC 码表
     * @param cd 辅助数组
     * @param depth 递归深度
     * @param index 该层要处理的结点下标
     */
    void Build_Tree(TREENODE * tempTree, char ** de_HC, char * cd, int depth, int index);
    /**
     * @brief BM算法
     * 
     * @param target 主串
     * @param pattern 模式串
     * @param pos 存储模式串初始位置的数组
     * @param inx 数组下标
     * @param posindex 在整个文件中的位置
     */
    void BM(char * target, char * pattern, int * pos, int &inx, int posindex);
    /**
     * @brief BM算法子函数，构造坏字符数组
     * 
     * @param pattern 模式串
     * @param badChar 坏字符数组
     */
    void GenerateBadChar(char * pattern, int * badChar);
    /**
     * @brief BM算法子函数，构造好后缀数组
     * 
     * @param pattern 模式串
     * @param suffix 后缀数组
     * @param prefix 如果公共后缀子串也是模式串的前缀子串,则值为1
     */
    void GenerateGoodSuffix(char * pattern, int * suffix, int * prefix);
    /**
     * @brief BM算法子函数，用好后缀数组移动主串
     * 
     * @param badIndex 坏字符对应的模式串中的字符下标
     * @param plen 模式串长度
     * @param suffix 后缀数组
     * @param prefix 如果公共后缀子串也是模式串的前缀子串,则值为1
     * @return int 主串与模式串第一个匹配的字符的位置,无则返回-1
     */
    int MoveByGoodSuffix(int badIndex, int plen, int * suffix, int * prefix);
    /**
     * @brief 依据输入的值搜索源文件
     * 
     */
    void SearchOrigin();
    /**
     * @brief 依据输入的值搜索二进制文件
     * 
     */
    void SearchBinary();
    /**
     * @brief 搜索二进制文件用的BM算法
     * 
     * @param target 主串
     * @param pattern 模式串
     * @param args 参数的结构体，包括pos数组，length：已处理的二进制数字个数，startpos:表明源文件的每个字符对应二进制文件中以位为单位的第几位
     * @param inx pos数组的下标
     * @param index 主串中的下标
     * @param floatflag startpos中的浮标
     */
    void BM_SearchBinary(char * target, char * pattern, ARGS args, int &inx,int &index, int &floatflag);
    /**
     * @brief 生成startpos函数
     * 
     * @param startpos 明源文件的每个字符对应二进制文件中以位为单位的第几位
     * @param filename 文件名
     */
    void GenerateStartpos(int * startpos, char * filename);
    /**
     * @brief 检查后缀是否为.wxl
     * 
     * @param str 字符串
     * @return int 是为1，不是为0
     */
    int judge_wxl(char * str);
};
