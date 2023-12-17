#pragma once
#include <string>
#include <unordered_map>
#include "Point.h"
#include "BinTree.h"

void print(BinTree<Point>* tree) {
	std::vector<std::vector<BinNode<Point>*>> visit;
	std::unordered_map<BinNode<Point>*, int> location;
	visit.push_back(std::vector<BinNode<Point>*>());
	if (tree->root) {
		visit[0].push_back(tree->root);
		location[tree->root] = 0;
	}
	while (!visit[visit.size() - 1].empty()) {
		visit.push_back(std::vector<BinNode<Point>*>());
		for (int i = 0; i < visit[visit.size() - 2].size(); i++) {
			if (visit[visit.size() - 2][i]->lc) {
				visit[visit.size() - 1].push_back(visit[visit.size() - 2][i]->lc);
				location[visit[visit.size() - 2][i]->lc] = 2 * location[visit[visit.size() - 2][i]];
			}
			if (visit[visit.size() - 2][i]->rc) {
				visit[visit.size() - 1].push_back(visit[visit.size() - 2][i]->rc);
				location[visit[visit.size() - 2][i]->rc] = 2 * location[visit[visit.size() - 2][i]] + 1;
			}
		}
	}
	visit.pop_back();
	std::vector<std::string> image(2 * visit.size() - 1, std::string(pow(2, visit.size() + 1) - 1, ' '));
	for (int i = 0; i < visit.size(); i++) {
		for (int j = 0; j < visit[i].size(); j++) {
			if (IsRed(visit[i][j])) {
				image[2 * i][(2 * location[visit[i][j]] + 1) * pow(2, visit.size() - i) - 2] = 'R';
			}
			else {
				image[2 * i][(2 * location[visit[i][j]] + 1) * pow(2, visit.size() - i) - 2] = 'B';
			}
			image[2 * i][(2 * location[visit[i][j]] + 1) * pow(2, visit.size() - i) - 1] = static_cast<char>(visit[i][j]->data.x / 10 + '0');
			image[2 * i][(2 * location[visit[i][j]] + 1) * pow(2, visit.size() - i)] = static_cast<char>(visit[i][j]->data.x % 10 + '0');
			if (i > 0) {
				image[2 * i - 1][(2 * location[visit[i][j]] + 1) * pow(2, visit.size() - i) - 1] = '|';
				if (IsLChild(*(visit[i][j]))) {
					for (int k = (2 * location[visit[i][j]] + 1) * pow(2, visit.size() - i) - 1; k < (2 * location[visit[i][j]->parent] + 1) * pow(2, visit.size() - i + 1) - 2; k++) {
						image[2 * i - 2][k] = '-';
					}
				}
				else {
					for (int k = (2 * location[visit[i][j]->parent] + 1) * pow(2, visit.size() - i + 1) + 1; k < (2 * location[visit[i][j]] + 1) * pow(2, visit.size() - i); k++) {
						image[2 * i - 2][k] = '-';
					}
				}
			}
		}
	}
	for (int i = 0; i < image.size(); i++) {
		std::cout << image[i] << std::endl;
	}
}
