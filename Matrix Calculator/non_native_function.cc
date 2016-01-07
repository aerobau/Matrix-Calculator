//
//  non_native_function.cpp
//  Matrix Calculator
//
//  Created by Alexander Robau on 12/29/15.
//  Copyright © 2015 Robau inc. All rights reserved.
//

#include "non_native_function.h"
#include "visitor.h"
#include "line_parser.h"
#include "printer.h"

NonNativeFunction::NonNativeFunction(std::vector<std::string> inputs,
                                     std::vector<std::string> outputs,
                                     FunctionDelegateInterface& delegate,
                                     std::string function_body)
        : function_delegate_(delegate) {
    for (auto iter = inputs.begin(); iter != inputs.end(); ++iter) {
        // Initialize mapping and assign corresponding inputs pointer at correct
        // input index
        local_variables_[*iter] = MathMatrix();
        inputs_.push_back(&local_variables_[*iter]);
    }
    for (auto iter = outputs.begin(); iter != outputs.end(); ++iter) {
        // Initialize mapping and assign corresponding outputs pointer at
        // correct outputs index
        local_variables_[*iter] = MathMatrix();
        outputs_.push_back(&local_variables_[*iter]);
    }
    set_function_body(function_body);
}

std::vector<MathMatrix> NonNativeFunction::
Execute(const std::vector<MathMatrix> inputs) {
    if (inputs.size() != inputs_count()) {
        std::string err = "Function parameter count mismatch";
        throw std::invalid_argument(err);
        return {};
    } else {
        std::vector<MathMatrix> outputs(outputs_count());
        // Assign all of the relevant local variables for the inputs to the
        // input parameters
        auto iter = inputs_.begin();
        for (auto it = inputs.begin(); it < inputs.end(); ++it, ++iter) {
            **iter = *it;
        }
        
        std::unique_ptr<Printer> printer(new Printer(nullptr));
        Visitor v(*this, function_delegate_, *printer);
        for (auto it = syntax_trees_.begin(); it != syntax_trees_.end(); ++it) {
            it->get()->Accept(v);
        }
        
        iter = outputs_.begin();
        for (auto it = outputs.begin(); it != outputs.end(); ++it, ++iter) {
            *it = **iter;
        }
        
        ResetLocalVariables();
        return outputs;
    }
}

int NonNativeFunction::inputs_count() const {
    return (int) inputs_.size();
}

int NonNativeFunction::outputs_count() const {
    return (int) outputs_.size();
}

bool NonNativeFunction::GetVariable(std::string name, MathMatrix& value) const {
    auto location = local_variables_.find(name);
    if (location == local_variables_.end()) {
        // Mapping to name doesn't exist, return false
        return false;
    } else {
        // Mapping to name does exist, assign to value and return true
        value = location->second;
        return true;
    }
}

void NonNativeFunction::SetVariable(std::string name, const MathMatrix& value) {
    local_variables_[name] = value;
}

std::string NonNativeFunction::function_body() const {
    return function_body_;
}

void NonNativeFunction::set_function_body(std::string function_body) {
    function_body_ = function_body;
    std::stringstream stream(function_body_);
    std::string line;
    syntax_trees_.clear();
    while (getline(stream, line)) {
        LineParser parser(line);
        syntax_trees_.push_back(std::move(parser.Parse()));
    }
}

void NonNativeFunction::ResetLocalVariables() {
    for (auto iter = local_variables_.begin(); iter != local_variables_.end();
         ++iter) {
        iter->second = MathMatrix();  // Reset to empty matrix
    }
}