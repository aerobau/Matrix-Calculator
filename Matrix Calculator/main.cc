//  main.cc
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/19/15.
//  Copyright © 2015 Robau inc. All rights reserved.

#include <iostream>
#include "session.h"

int main() {
    std::string in;
    bool done = false;
    while (!done) {
        std::cout << "Press 'L' to load a Session in this directory or 'N' "
                  << "to create a new one. Press 'X' to exit" << std::endl;
        std::getline(std::cin, in);
        if (in == "L" || in == "l") {
            std::cout << "Loading not supported yet" << std::endl;
        } else if (in == "N" || in == "n") {
            Session s; s.Start();
        } else if (in == "X" || in == "x") {
            done = true;
        } else {
            std::cout << "Invalid input" << std::endl;
        }
    }
}

