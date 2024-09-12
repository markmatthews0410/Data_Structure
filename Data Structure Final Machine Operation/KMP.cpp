/*
 * @Author: Brad D. Madden（黄浩轩）
 * @Date: 2024/1/21 14:55:36
 * @LastEditors: Brad D. Madden（黄浩轩）
 * @LastEditTime: 2024/1/21 14:55:36
 * @Description: 这是一个可统计字符、单词、空格和标点数量，支持查找和替换指定单词，使用KMP算法定位单词位置，并保存替换结果到文件的文本处理程序。
 * @Contact: 22009200366@stu.xidian.edu.cn
 * @Copyright: © 2024 Brad D. Madden.
 * All rights reserved.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define max_word_length 50  // 定义最大单词长度

// 函数声明
void count_characters(const char *, int *, int *, int *);
void find_target(const char *, const char *);
void kmp(const char *, const char *, int *);
char *find_and_replace_target(const char *, const char *, const char *);
void replace_word(char *, const char *, const char *);
void save_to_file(const char *, const char *);

int total = 0;  // 用于记录目标单词出现的总次数

int main()
{
    FILE *file = fopen("essay.txt", "r");  // 打开文件 "essay.txt" 以读取模式
    if (file == NULL)
    {
        printf("Error opening file.\n");  // 如果文件打开失败，输出错误信息
        return 1;
    }
    char *text = (char *)malloc(1);  // 动态分配内存来存储文本内容
    if (text == NULL)
    {
        printf("Memory allocation error.\n");  // 如果内存分配失败，输出错误信息
        fclose(file);
        return 1;
    }
    int filesize = 1;
    int index = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        text[index++] = ch;
        text = (char *)realloc(text, filesize + 1);  // 动态调整内存大小
        if (text == NULL)
        {
            printf("Memory allocation error.\n");  // 如果内存分配失败，输出错误信息
            fclose(file);
            free(text);
            return 1;
        }
        filesize++;
    }
    text[index] = '\0';  // 在文本末尾添加空字符，表示字符串结束
    fclose(file);
    int word_count, space_count, punctuation_count;
    count_characters(text, &word_count, &space_count, &punctuation_count);  // 统计字符数
    printf("Word Count: %d\n", word_count);  // 输出单词数
    printf("Space Count: %d\n", space_count);  // 输出空格数
    printf("Punctuation Count: %d\n", punctuation_count);  // 输出标点符号数
    printf("Enter the target word to find:");  // 提示用户输入要查找的目标单词
    char target[max_word_length];
    scanf("%s", target);  // 读取用户输入的目标单词
    printf("Replace or Not?(Please Input 1 (Yes) or 0 (No)):");  // 提示用户是否替换目标单词
    int flag;
    scanf("%d", &flag);
    if (flag == 0)
        find_target(text, target);  // 如果选择不替换，则查找目标单词
    else
    {
        char replacement[max_word_length];
        printf("Please Input Replacement:");  // 提示用户输入替换的单词
        scanf("%s", replacement);
        text = find_and_replace_target(text, target, replacement);  // 查找并替换目标单词
        save_to_file("output.txt", text);  // 将修改后的文本保存到文件 "output.txt"
    }
    printf("target occurrences in total: %d\n", total);  // 输出目标单词的总出现次数
    free(text);  // 释放动态分配的内存
    return 0;
}

// 统计字符数的函数
void count_characters(const char *text, int *word_count, int *space_count, int *punctuation_count)
{
    *word_count = 0;            // 初始化单词数为0
    *space_count = 0;           // 初始化空格数为0
    *punctuation_count = 0;     // 初始化标点符号数为0
    int i = 0;                  // 文本指针的位置

    // 遍历文本，统计单词数、空格数和标点符号数
    while (text[i] != '\0')
    {
        if (isalpha(text[i]))   // 如果当前字符是字母
        {
            (*word_count)++;    // 增加单词数
            while (isalpha(text[i]))
                i++;             // 跳过当前单词的所有字母
        }
        else if (isspace(text[i]) && text[i] != '\n')  // 如果当前字符是空格
        {
            (*space_count)++;   // 增加空格数
            i++;                // 移动文本指针
        }
        else if (ispunct(text[i]))  // 如果当前字符是标点符号
        {
            (*punctuation_count)++;  // 增加标点符号数
            i++;                    // 移动文本指针
        }
        else
            i++;                // 其他情况，移动文本指针
    }
}

// 在文本中查找目标单词的函数
void find_target(const char *text, const char *target)
{
    int line_number = 1;                // 记录当前行号
    const char *line_start = text;      // 指向当前行的起始位置
    int m = strlen(target);             // 目标单词的长度

    // 遍历整个文本
    while (*text != '\0')
    {
        // 当遇到换行符或文本结束时，处理当前行
        if (*text == '\n' || *text == '\0')
        {
            int line_length = text - line_start;  // 计算当前行的长度
            char *line_text = (char *)malloc(line_length + 1);  // 为当前行文本分配内存
            strncpy(line_text, line_start, line_length);  // 复制当前行文本
            line_text[line_length] = '\0';  // 添加字符串结束符
            int occurrence = 0;  // 用于记录目标单词在当前行的出现次数
            kmp(target, line_text, &occurrence);  // 使用KMP算法查找目标单词在当前行的出现次数
            total += occurrence;  // 更新总出现次数
            if (occurrence != 0)
                printf("line:%d  occurrences:%d\n", line_number, occurrence);  // 输出当前行号和目标单词的出现次数
            free(line_text);  // 释放当前行文本的内存
            line_number++;  // 更新行号
            line_start = text + 1;  // 指向下一行的起始位置
        }
        text++;
    }

    // 处理最后一行（如果没有换行符的情况）
    if (line_start < text)
    {
        int line_length = text - line_start;  // 计算最后一行的长度
        char *line_text = (char *)malloc(line_length + 1);  // 为最后一行文本分配内存
        strncpy(line_text, line_start, line_length);  // 复制最后一行文本
        line_text[line_length] = '\0';  // 添加字符串结束符
        int occurrence = 0;  // 用于记录目标单词在最后一行的出现次数
        kmp(target, line_text, &occurrence);  // 使用KMP算法查找目标单词在最后一行的出现次数
        if (occurrence != 0)
            printf("line:%d  occurrences:%d\n", line_number, occurrence);  // 输出最后一行的行号和目标单词的出现次数
            total += occurrence;  // 更新总出现次数
        free(line_text);  // 释放最后一行文本的内存
    }
}

// 替换目标单词的函数
void replace_word(char *line_text, const char *target, const char *replacement)
{
    int target_length = strlen(target);            // 目标单词的长度
    int replacement_length = strlen(replacement);  // 替换单词的长度
    char *replace_pos = line_text;                 // 指向目标单词首次出现的位置

    // 循环替换目标单词，直到目标单词不再出现在当前行
    while ((replace_pos = strstr(replace_pos, target)) != NULL)
    {
        // 移动目标单词后面的文本，为替换单词腾出空间
        memmove(replace_pos + replacement_length, replace_pos + target_length, strlen(replace_pos + target_length) + 1);
        
        // 将替换单词拷贝到目标单词的位置
        memcpy(replace_pos, replacement, replacement_length);
        
        // 将指针移动到替换单词后面
        replace_pos += replacement_length;
    }
}

// 查找并替换目标单词的函数
char *find_and_replace_target(const char *text, const char *target, const char *replacement)
{
    int line_number = 1;                          // 记录当前行号
    const char *line_start = text;                // 指向当前行的起始位置
    int m = strlen(target);                       // 目标单词的长度
    char *result_text = (char *)malloc(strlen(text) + 1);  // 用于存储替换后的文本
    strcpy(result_text, "");                     // 初始化为空字符串

    // 遍历整个文本
    while (*text != '\0')
    {
        // 当遇到换行符或文本结束时，处理当前行
        if (*text == '\n' || *text == '\0')
        {
            int line_length = text - line_start;  // 计算当前行的长度
            char *line_text = (char *)malloc(line_length + 1);  // 为当前行文本分配内存
            strncpy(line_text, line_start, line_length);  // 复制当前行文本
            line_text[line_length] = '\0';  // 添加字符串结束符
            int occurrence = 0;  // 用于记录目标单词在当前行的出现次数
            kmp(target, line_text, &occurrence);  // 使用KMP算法查找目标单词在当前行的出现次数
            total += occurrence;  // 更新总出现次数
            if (occurrence != 0)
            {
                printf("line:%d  occurrences:%d\n", line_number, occurrence);  // 输出当前行号和目标单词的出现次数
                replace_word(line_text, target, replacement);  // 替换当前行中的目标单词
            }

            // 将替换后的行文本追加到结果文本中，并添加换行符
            strcat(result_text, line_text);
            strcat(result_text, "\n");

            free(line_text);  // 释放当前行文本的内存
            line_number++;    // 更新行号
            line_start = text + 1;  // 指向下一行的起始位置
        }
        text++;
    }

    // 处理最后一行（如果没有换行符的情况）
    if (line_start < text)
    {
        int line_length = text - line_start;  // 计算最后一行的长度
        char *line_text = (char *)malloc(line_length + 1);  // 为最后一行文本分配内存
        strncpy(line_text, line_start, line_length);  // 复制最后一行文本
        line_text[line_length] = '\0';  // 添加字符串结束符
        int occurrence = 0;  // 用于记录目标单词在最后一行的出现次数
        kmp(target, line_text, &occurrence);  // 使用KMP算法查找目标单词在最后一行的出现次数
        if (occurrence != 0)
        {
            printf("line:%d  occurrences:%d\n", line_number, occurrence);  // 输出最后一行的行号和目标单词的出现次数
            total += occurrence;  // 更新总出现次数
            replace_word(line_text, target, replacement);  // 替换最后一行中的目标单词
        }

        // 将替换后的最后一行文本追加到结果文本中
        strcat(result_text, line_text);
        free(line_text);  // 释放最后一行文本的内存
    }

    return result_text;  // 返回替换后的文本
}

// 构建KMP算法的辅助数组
void build_next(const char *pattern, int *next)
{
    int m = strlen(pattern);       // 目标单词的长度
    int i = 0, j = -1;              // i和j分别表示辅助数组next的当前位置
    next[0] = -1;                   // 初始化next数组的第一个元素为-1

    // 遍历目标单词的每个字符，构建辅助数组next
    while (i < m)
    {
        // 如果j为-1（表示前缀和后缀没有匹配），或者当前字符匹配
        if (j == -1 || pattern[i] == pattern[j])
        {
            i++;                    // 移动目标单词的指针
            j++;                    // 移动next数组的指针
            next[i] = j;            // 设置next数组的当前位置的值
        }
        else
            j = next[j];            // 回溯到前一个位置，继续匹配
    }
}

// KMP算法实现，用于查找目标单词的出现位置
void kmp(const char *pattern, const char *text, int *occurrence)
{
    int m = strlen(pattern);       // 目标单词的长度
    int n = strlen(text);          // 当前行文本的长度
    int next[m];                    // 部分匹配表，用于加速匹配过程
    build_next(pattern, next);      // 构建部分匹配表

    int i = 0, j = 0;               // i和j分别表示text和pattern的当前位置
    *occurrence = 0;                // 用于记录目标单词在当前行的出现次数

    // 遍历当前行的文本
    while (i < n)
    {
        if (pattern[j] == text[i])  // 如果当前字符匹配
        {
            j++;                    // 移动pattern的指针
            i++;                    // 移动text的指针
        }

        if (j == m)                 // 如果已经完全匹配了整个pattern
        {
            (*occurrence)++;        // 增加目标单词的出现次数
            printf("position:%d\n", i - j + 1);  // 输出目标单词首次出现的位置
            j = 0;                  // 重新开始匹配下一个目标单词
        }
        else if (i < n && pattern[j] != text[i])  // 如果当前字符不匹配
        {
            if (j != 0)
                j = next[j];        // 回溯到部分匹配表中的位置
            else
                i++;                // 移动text的指针
        }
    }
}

// 在一行中替换目标单词的函数
void replace_in_line(char *line_text, const char *target, const char *replacement)
{
    int m = strlen(target);               // 目标单词的长度
    char *replace_pos = line_text;         // 指向目标单词首次出现的位置

    // 循环替换目标单词，直到目标单词不再出现在当前行
    while ((replace_pos = strstr(replace_pos, target)) != NULL)
    {
        // 移动目标单词后面的文本，为替换单词腾出空间
        memmove(replace_pos + strlen(replacement), replace_pos + m, strlen(replace_pos + m) + 1);
        
        // 将替换单词拷贝到目标单词的位置
        memcpy(replace_pos, replacement, strlen(replacement));
        
        // 将指针移动到替换单词后面
        replace_pos += strlen(replacement);
    }
}

// 将文本保存到文件的函数
void save_to_file(const char *filename, const char *text)
{
    FILE *file = fopen(filename, "w");  // 以写入模式打开文件
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");  // 如果文件打开失败，输出错误信息
        return;
    }

    fwrite(text, sizeof(char), strlen(text), file);  // 将文本写入文件
    fclose(file);  // 关闭文件
}