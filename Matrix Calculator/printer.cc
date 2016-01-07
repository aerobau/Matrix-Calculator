//  printer.cc
//  Matrix Calculator
//
//  Created by Alexander Robau on 1/5/16.

#include "printer.h"

Printer::Printer(std::ostream* stream)
        : print_(""), valid_(false), stream_(stream) {}

void Printer::Print() const {
    if (stream_) *stream_ << print_ << std::endl;
}

bool Printer::valid() const {
    return valid_;
}

void Printer::set_data(std::string data) {
    print_ = data;
}

void Printer::set_valid(bool valid) {
    valid_ = valid;
}

void Printer::set_stream(std::ostream* stream) {
    stream_ = stream;
}