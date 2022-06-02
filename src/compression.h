/**
 * @file compression.h
 * @author your name (you@domain.com)
 * @brief ѹ���㷨ʵ��
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
#define N 128//128����ת���ַ�������
typedef int WeightType;//Ȩ�ص�����
using namespace std;
/**
 * @brief huffman���洢��Ԫ
 * 
 */
typedef struct
{
    WeightType weight;
    int parent, lc, rc;
}HTNODE;
/**
 * @brief �洢��N - 1���������Һ��ӵĴ洢��Ԫ
 * 
 */
typedef struct
{
    int lc, rc;
}TREENODE;
/**
 * @brief �����Ľṹ��
 * 
 */
typedef struct
{
    int * pos;
    int length;
    int * startpos;
}ARGS;
typedef HTNODE HuffmanTree[2 * N];//huffman���Ĵ洢�ռ�
class compression
{
private:
    /* data */
public:
    compression(/* args */);
    ~compression();
    /**
     * @brief �������ִ�к���
     * 
     */
    bool Code(string inRoad, string outRoad);
    /**
     * @brief ����һ�Ź�������
     * 
     * @param ht �Ѿ���ʼ���Ĺ�������
     */
    void CreateHT(HuffmanTree ht);
    /**
     * @brief ���������봴�����
     * 
     * @param HC ����ά��̬����
     * @param cd ��������
     * @param ht �Ѿ������Ĺ�������
     */
    void HuffmanCoding(char ** HC, char * cd, HuffmanTree ht);
    /**
     * @brief ��ӡ��������ã�
     * 
     * @param HC ���
     */
    void PrintCodeList(char ** HC);
    /**
     * @brief �������ִ�к���
     * 
     */
    bool Decode(string inRoad, string outRoad);
    /**
     * @brief �ݹ鴴����������
     * 
     * @param tempTree �洢����������������Ϣ
     * @param de_HC ���
     * @param cd ��������
     * @param depth �ݹ����
     * @param index �ò�Ҫ����Ľ���±�
     */
    void Build_Tree(TREENODE * tempTree, char ** de_HC, char * cd, int depth, int index);
    /**
     * @brief BM�㷨
     * 
     * @param target ����
     * @param pattern ģʽ��
     * @param pos �洢ģʽ����ʼλ�õ�����
     * @param inx �����±�
     * @param posindex �������ļ��е�λ��
     */
    void BM(char * target, char * pattern, int * pos, int &inx, int posindex);
    /**
     * @brief BM�㷨�Ӻ��������컵�ַ�����
     * 
     * @param pattern ģʽ��
     * @param badChar ���ַ�����
     */
    void GenerateBadChar(char * pattern, int * badChar);
    /**
     * @brief BM�㷨�Ӻ���������ú�׺����
     * 
     * @param pattern ģʽ��
     * @param suffix ��׺����
     * @param prefix ���������׺�Ӵ�Ҳ��ģʽ����ǰ׺�Ӵ�,��ֵΪ1
     */
    void GenerateGoodSuffix(char * pattern, int * suffix, int * prefix);
    /**
     * @brief BM�㷨�Ӻ������úú�׺�����ƶ�����
     * 
     * @param badIndex ���ַ���Ӧ��ģʽ���е��ַ��±�
     * @param plen ģʽ������
     * @param suffix ��׺����
     * @param prefix ���������׺�Ӵ�Ҳ��ģʽ����ǰ׺�Ӵ�,��ֵΪ1
     * @return int ������ģʽ����һ��ƥ����ַ���λ��,���򷵻�-1
     */
    int MoveByGoodSuffix(int badIndex, int plen, int * suffix, int * prefix);
    /**
     * @brief ���������ֵ����Դ�ļ�
     * 
     */
    void SearchOrigin();
    /**
     * @brief ���������ֵ�����������ļ�
     * 
     */
    void SearchBinary();
    /**
     * @brief �����������ļ��õ�BM�㷨
     * 
     * @param target ����
     * @param pattern ģʽ��
     * @param args �����Ľṹ�壬����pos���飬length���Ѵ���Ķ��������ָ�����startpos:����Դ�ļ���ÿ���ַ���Ӧ�������ļ�����λΪ��λ�ĵڼ�λ
     * @param inx pos������±�
     * @param index �����е��±�
     * @param floatflag startpos�еĸ���
     */
    void BM_SearchBinary(char * target, char * pattern, ARGS args, int &inx,int &index, int &floatflag);
    /**
     * @brief ����startpos����
     * 
     * @param startpos ��Դ�ļ���ÿ���ַ���Ӧ�������ļ�����λΪ��λ�ĵڼ�λ
     * @param filename �ļ���
     */
    void GenerateStartpos(int * startpos, char * filename);
    /**
     * @brief ����׺�Ƿ�Ϊ.wxl
     * 
     * @param str �ַ���
     * @return int ��Ϊ1������Ϊ0
     */
    int judge_wxl(char * str);
};