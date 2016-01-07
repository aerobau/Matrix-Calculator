//  printer.h
//  Matrix Calculator
//
//  Created by Alexander Robau on 1/5/16.

#ifndef PRINTER_H_
#define PRINTER_H_

#include <string>
#include <iostream>

class Printer {
public:
    Printer(std::ostream* stream);
    
    // Function that prints the desired string print_ to the desired stream
    // stream_.  More often than not this is the std::cout
    void Print() const;
    
    // Function that accesses the valid flag boolean to tell whether or not the
    // printer is valid and should be used
    bool valid() const;
    
    // Function to access hwat the printer is currently set to print, used to
    // alter the string as the user input is being read.
    std::string data() const;
    
    
    // Function to set what the printer is printing
    void set_data(std::string);
    void set_valid(bool);
    void set_stream(std::ostream*);
    
private:
    // String that holds what is to be printed by the printer.  This is altered
    // throughout reading of user input to get the appropriate function.
    std::string print_;
    
    // Flag that defines whether or not a printer is valid and should be used
    bool valid_;
    
    // Unowned pointer to the stream that is being printed to, used pointer for
    // ability to interchange streams and not have a stream at all
    std::ostream* stream_;
    
};

#endif // PRINTER_H_
