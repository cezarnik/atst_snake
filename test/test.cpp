//
// Created by kolya on 07.11.19.
//
#include "src/Config/Globals.hpp"
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

void testMoveUp() {
    Board board(10, 10, Board::Style::SOLID);
    Player player(5, 5);
    player.move(Player::UP);
    player.update(&board);
    assert(player.getX() == 5 && player.getY() == 4);
}

void testMoveDown() {
    Board board(10, 10, Board::Style::SOLID);
    Player player(5, 5);
    player.move(Player::DOWN);
    player.update(&board);
    assert(player.getX() == 5 && player.getY() == 6);
}

void testMoveLeft() {
    Board board(10, 10, Board::Style::SOLID);
    Player player(5, 5);
    player.move(Player::LEFT);
    player.update(&board);
    assert(player.getX() == 4 && player.getY() == 5);
}

void testMoveRight() {
    Board board(10, 10, Board::Style::SOLID);
    Player player(5, 5);
    player.move(Player::RIGHT);
    player.update(&board);
    assert(player.getX() == 6 && player.getY() == 5);
}

void testWallsNormal() {
    std::mt19937 mt(19);
    std::uniform_int_distribution<int> un(1, 100);
    std::uniform_int_distribution<int> un_wall(0, 1);
    using std::vector;
    const int tests_number = 50;

    for (int i = 1; i <= tests_number; ++i) {
        int width = un(mt);
        int height = un(mt);
        Board board(width, height, Board::Style::TELEPORT);
        vector<vector<bool>> new_board(height, vector<bool>(width));
        for (int j = 0; j < width; ++j) {
            new_board[0][j] = 0;
            new_board[height - 1][j] = 0;
        }
        for (int j = 0; j < height; ++j) {
            new_board[j][0] = 0;
            new_board[j][width - 1] = 0;
        }
        for (int i = 1; i + 1 < width; ++i) {
            for (int j = 1; j + 1 < height; ++j) {
                new_board[j][i] = un_wall(mt);
            }
        }
        board.setBoard(new_board);
        for (int i = 0; i < width; ++i) {
            for (int e = 0; e < height; ++e) {
                assert(new_board[e][i] == board.isWall(i, e));
            }
        }
    }
    for (int i = 1; i <= tests_number; ++i) {
        int width = un(mt);
        int height = un(mt);
        Board board(width, height, Board::Style::SOLID);
        vector<vector<bool>> new_board(height, vector<bool>(width));
        for (int j = 0; j < width; ++j) {
            new_board[0][j] = 1;
            new_board[height - 1][j] = 1;
        }
        for (int j = 0; j < height; ++j) {
            new_board[j][0] = 1;
            new_board[j][width - 1] = 1;
        }
        for (int i = 1; i + 1 < width; ++i) {
            for (int j = 1; j + 1 < height; ++j) {
                new_board[j][i] = un_wall(mt);
            }
        }
        board.setBoard(new_board);
        for (int i = 0; i < width; ++i) {
            for (int e = 0; e < height; ++e) {
                assert(new_board[e][i] == board.isWall(i, e));
            }
        }
    }

}

void testWallsAbnormal() {
    std::mt19937 mt(19);
    std::uniform_int_distribution<int> un(1, 10);
    std::uniform_int_distribution<int> un_wall(0, 1);
    using std::vector;
    const int tests_number = 1000;

    for (int i = 1; i <= tests_number; ++i) {
        int width = un(mt);
        int height = un(mt);
        Board board(width, height, Board::Style::TELEPORT);
        vector<vector<bool>> new_board(height, vector<bool>(width));
        for (int j = 0; j < width; ++j) {
            for (int e = 0; e < height; ++e) {
                new_board[e][j] = un_wall(mt);
            }
        }
        board.setBoard(new_board);
        for (int i = 0; i < width; ++i) {
            for (int e = 0; e < height; ++e) {
                assert(new_board[e][i] == board.isWall(i, e));
            }
        }
    }
    for (int i = 1; i <= tests_number; ++i) {
        int width = un(mt);
        int height = un(mt);
        Board board(width, height, Board::Style::SOLID);
        vector<vector<bool>> new_board(width, vector<bool>(height));
        for (int j = 0; j < width; ++j) {
            for (int e = 0; e < height; ++e) {
                new_board[j][e] = un_wall(mt);
            }
        }
        board.setBoard(new_board);
        for (int i = 0; i < width; ++i) {
            for (int e = 0; e < height; ++e) {
                assert(new_board[e][i] == board.isWall(i, e));
            }
        }
    }
    Board board(0, 0, Board::Style::SOLID);
}

int main() {
    testAppleCount();
    testWallsNormal();
    testMoveUp();
    testMoveDown();
//    testMoveLeft();
    testMoveRight();
}
