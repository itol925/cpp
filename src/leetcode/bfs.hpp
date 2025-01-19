#include <iostream>
#include <vector>
#include <stack>
#include <numeric>
#include <queue>
#include <unordered_set>
#include "common/common.hpp"

using namespace std;
using namespace common;

/**
 * 广度优先搜索 breadth-first-search
 * 从树根起一层一层遍历
 */
namespace leetcode::bfs {
    namespace shortest_bridge {
        /**
         * 给定一个二维0-1矩阵，其中1表示陆地，0表示海洋，每个位置与上下左右相连，已知矩阵中有眀只有两个岛屿，求最少要填海造陆多少个位置才可以
         * 将两个岛屿相连.
         * 思路：找两个岛屿的最短距离
         * https://leetcode.cn/problems/shortest-bridge/description/
         */
        void bfs_find_one(vector<vector<int>> &grid, int r, int c) {
            if (r < 0 || r > grid.size() - 1 || c < 0 || c > grid[0].size() - 1) {
                return;
            }
            if (grid[r][c] == 2 || grid[r][c] == 0) {
                return;
            }
            grid[r][c] = 2;
            bfs_find_one(grid, r-1, c);
            bfs_find_one(grid, r+1, c);
            bfs_find_one(grid, r, c-1);
            bfs_find_one(grid, r, c+1);
        }

        int step_of_island(vector<vector<int>> &grid, int r, int c) {
            int step = -1;
            for (int i = r + 1; i < grid.size(); i++) { // 往下延伸
                if (grid[i][c] == 1) {
                    step = i - r;
                    break;
                }
            }
            for (int i = r - 1; i > 0; i--) { // 往上延伸
                if (grid[i][c] == 1) {
                    if (step == -1 || r - i < step) {
                        step = r - i;
                        break;
                    }
                }
            }
            for (int i = c + 1; i < grid[0].size(); i++) { // 往右延伸
                if (grid[r][i] == 1) {
                    if (step == -1 ||  i - c < step) {
                        step = i - c;
                        break;
                    }
                }
            }
            for (int i = c - 1; i > 0; i--) { // 往左延伸
                if (grid[r][i] == 1) {
                    if (step == -1 || c - i < step) {
                        step = c - i;
                        break;
                    }
                }
            }
            return step - 1;
        }
        int do_shortest_bridge(vector<vector<int>> &grid) {
            // 先找到其中一个岛屿，将值置为2
            bool find_island = false;
            for (int r = 0; r < grid.size(); r++) {
                for (int c = 0; c < grid[0].size(); c++) {
                    if (grid[r][c]) {
                        bfs_find_one(grid, r, c);
                        cout << "grid:" << array_to_string(grid) << endl;
                        find_island = true;
                        break;
                    }
                }
                if (find_island) {
                    break;
                }
            }

            // 遍历每一个值为2的点（即找到的第一个岛屿的点），不停往外延伸，直到找到值为1的点，延伸的步数即为距离
            int level = -1;
            for (int r = 0; r < grid.size(); r++) {
                for (int c = 0; c < grid[0].size(); c++) {
                    if (grid[r][c] == 2) {
                        int l = step_of_island(grid, r, c);
                        if (l > 0) {
                            if (level == -1 || l < level) {
                                level = l;
                            }
                        }
                    }
                }
            }
            return level;
        }
        void test() {
            vector<vector<int>> grid = {
                    {1, 1, 1, 1, 1},
                    {1, 0, 0, 0, 0},
                    {1, 0, 0, 0, 0},
                    {1, 0, 0, 0, 0},
                    {1, 0, 0, 0, 1},
            };

            //vector<vector<int>> grid = {
            //        {1, 1, 1, 1},
            //        {1, 0, 0, 0},
            //        {1, 0, 0, 0},
            //        {1, 0, 0, 1},
            //};
            cout << "shortest_bridge:" << do_shortest_bridge(grid) << endl;
        }
    }

    namespace word_ladder_ii {
        /**
         * 给定一个起始字符串和一个终止字符串以及一个单词表，求是否可以将起始字符串每次改一个字符，直到改成终止字符串，
         * 且所有中间修改过程表示的字符串都可以在单词表中找到，若存在，输出需要修改次数最少的所有一更改方式
         * 比如：
         * input: beginWord="hit", endWord="cot", wordList=["hot", "dot", "dog", "lot", "log", "cog"]
         * output: [["hit", "hot", "dot", "dog", "cog"], ["hit", "hot", "lot", "log", "cog"]]
         *
         * 思路：https://leetcode.cn/problems/word-ladder-ii/description/
         * 把每个单词都抽象为一个顶点，如果两个单词可以只改变一个字母进行转换，那么说明它们之间有一条双向边
         */
        void backtrack(vector<vector<string>> &res, const string &Node, unordered_map<string, set<string>> &from, vector<string> &path) {
            if (from[Node].empty()) {
                res.push_back({path.rbegin(), path.rend()});
                return;
            }
            for (const string &Parent: from[Node]) {
                path.push_back(Parent);
                backtrack(res, Parent, from, path);
                path.pop_back();
            }
        }
        vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList) {
            vector<vector<string>> res;
            // 因为需要快速判断扩展出的单词是否在 wordList 里，因此需要将 wordList 存入哈希表，这里命名为「字典」
            unordered_set<string> dict = {wordList.begin(), wordList.end()};
            // 修改以后看一下，如果根本就不在 dict 里面，跳过
            if (dict.find(endWord) == dict.end()) {
                return res;
            }
            // 特殊用例处理
            dict.erase(beginWord);

            // 第 1 步：广度优先搜索建图
            // 记录扩展出的单词是在第几次扩展的时候得到的，key：单词，value：在广度优先搜索的第几层
            unordered_map<string, int> steps = {{beginWord, 0}};
            // 记录了单词是从哪些单词扩展而来，key：单词，value：单词列表，这些单词可以变换到 key ，它们是一对多关系
            unordered_map<string, set<string>> from = {{beginWord, {}}};
            int step = 0;
            bool found = false;
            queue<string> q = queue<string>{{beginWord}};
            int wordLen = beginWord.length();
            while (!q.empty()) {
                step++;
                int size = q.size();
                for (int i = 0; i < size; i++) {
                    const string currWord = std::move(q.front());
                    string nextWord = currWord;
                    q.pop();
                    // 将每一位替换成 26 个小写英文字母
                    for (int j = 0; j < wordLen; ++j) {
                        const char origin = nextWord[j];
                        for (char c = 'a'; c <= 'z'; ++c) {
                            nextWord[j] = c;
                            if (steps[nextWord] == step) {
                                from[nextWord].insert(currWord);
                            }
                            if (dict.find(nextWord) == dict.end()) {
                                continue;
                            }
                            // 如果从一个单词扩展出来的单词以前遍历过，距离一定更远，为了避免搜索到已经遍历到，且距离更远的单词，需要将它从 dict 中删除
                            dict.erase(nextWord);
                            // 这一层扩展出的单词进入队列
                            q.push(nextWord);
                            // 记录 nextWord 从 currWord 而来
                            from[nextWord].insert(currWord);
                            // 记录 nextWord 的 step
                            steps[nextWord] = step;
                            if (nextWord == endWord) {
                                found = true;
                            }
                        }
                        nextWord[j] = origin;
                    }
                }
                if (found) {
                    break;
                }
            }
            // 第 2 步：回溯找到所有解，从 endWord 恢复到 beginWord ，所以每次尝试操作 path 列表的头部
            if (found) {
                vector<string> Path = {endWord};
                backtrack(res, endWord, from, Path);
            }
            return res;
        }
         void test() {
             string beginWord = "hit", endWord = "cot";
             std::vector<string> wordList = {"hit", "hot", "dot", "dog", "lot", "log", "cog", "cot"};
             auto res = findLadders(beginWord, endWord, wordList);
             cout << "res:" << array_to_string(res) << endl;
         }
    }
}