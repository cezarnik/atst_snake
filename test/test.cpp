//
// Created by kolya on 07.11.19.
//
#include <src/Config/Globals.hpp>
#include <src/Entities/FruitManager.hpp>
#include <src/Entities/Board.hpp>
#include <src/Entities/Player.hpp>
#include <commander/commander.h>
#include <cassert>
#include <ncurses.h>
#include <random>
#include <iostream>

void testAppleCount() {
    // take fruits
    for (int fruits = -1; fruits <= 1000; ++fruits) {
        Board board(10, 10, Board::Style::SOLID);
        FruitManager fruitManager(fruits);
        assert(fruitManager.getAmount() == fruits);
        Player player(1, 1);
        fruitManager.update(&player, &board);
        assert(fruitManager.getAmount() == fruits);
    }
}

void testWalls() {
    std::mt19937 mt(19);
    std::uniform_int_distribution<int> un(4, 100);
    std::uniform_int_distribution<int> un_wall(0, 1);
    using std::vector;
    const int tests_number = 1000;

    for (int i = 1; i <= tests_number; ++i) {
        int width = un(mt);
        int height = un(mt);
        Board board(width, height, Board::Style::TELEPORT);
        Board empty_board(0, 0, Board::Style::TELEPORT);
        vector<vector<bool>> new_board(height, vector<bool>(width));
        for (int j = 1; j+1 < width; ++j) {
            for (int e = 0; e < height; ++e) {
                new_board[e][j] = un_wall(mt);
            }
        }
        board.setBoard(new_board);
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                std::cout << new_board[i][j] << " ";
            }
            std::cout << std::endl;
        }
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                std::cout << board.isWall(j, i) << " ";
            }
            std::cout << std::endl;
        }
        empty_board.setBoard(new_board);
        for (int i = 0; i < width; ++i) {
            for (int e = 0; e < height; ++e) {
                assert(new_board[e][i] == board.isWall(i, e));
                assert(new_board[e][i] == empty_board.isWall(i, e));
            }
        }
    }
    for (int i = 1; i <= tests_number; ++i) {
        int width = un(mt);
        int height = un(mt);
        Board board(width, height, Board::Style::SOLID);
        Board empty_board(0, 0, Board::Style::SOLID);
        vector<vector<bool>> new_board(width, vector<bool>(height));
        for (int j = 0; j < width; ++j) {
            for (int e = 0; e < height; ++e) {
                new_board[j][e] = un_wall(mt);
            }
        }
        board.setBoard(new_board);
        empty_board.setBoard(new_board);
        for (int i = 0; i < width; ++i) {
            for (int e = 0; e < height; ++e) {
                assert(new_board[e][i] == board.isWall(i, e));
                assert(new_board[e][i] == empty_board.isWall(i, e));
            }
        }
    }
}

void testWalls() {
    std::mt19937 mt(19);
    std::uniform_int_distribution<int> un(1, 10);
    std::uniform_int_distribution<int> un_wall(0, 1);
    using std::vector;
    const int tests_number = 1000;

    for (int i = 1; i <= tests_number; ++i) {
        int width = un(mt);
        int height = un(mt);
        Board board(width, height, Board::Style::TELEPORT);
        Board empty_board(0, 0, Board::Style::TELEPORT);
        vector<vector<bool>> new_board(height, vector<bool>(width));
        for (int j = 0; j < width; ++j) {
            for (int e = 0; e < height; ++e) {
                new_board[e][j] = un_wall(mt);
            }
        }
        board.setBoard(new_board);
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                std::cout << new_board[i][j] << " ";
            }
            std::cout << std::endl;
        }
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                std::cout << board.isWall(j, i) << " ";
            }
            std::cout << std::endl;
        }
        empty_board.setBoard(new_board);
        for (int i = 0; i < width; ++i) {
            for (int e = 0; e < height; ++e) {
                assert(new_board[e][i] == board.isWall(i, e));
                assert(new_board[e][i] == empty_board.isWall(i, e));
            }
        }
    }
    for (int i = 1; i <= tests_number; ++i) {
        int width = un(mt);
        int height = un(mt);
        Board board(width, height, Board::Style::SOLID);
        Board empty_board(0, 0, Board::Style::SOLID);
        vector<vector<bool>> new_board(width, vector<bool>(height));
        for (int j = 0; j < width; ++j) {
            for (int e = 0; e < height; ++e) {
                new_board[j][e] = un_wall(mt);
            }
        }
        board.setBoard(new_board);
        empty_board.setBoard(new_board);
        for (int i = 0; i < width; ++i) {
            for (int e = 0; e < height; ++e) {
                assert(new_board[e][i] == board.isWall(i, e));
                assert(new_board[e][i] == empty_board.isWall(i, e));
            }
        }
    }
}

int main() {
    testAppleCount();
    testWalls();
}