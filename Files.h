/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Files.h
 * Author: dmitriy
 *
 * Created on October 22, 2017, 10:20 PM
 */

#ifndef FILES_H
#define FILES_H

#include "Cache.h"

//const char *fileName = "test.txt";

int read_file(char *, struct Hash *); //read

int write_file(char *, struct Hash *); //write

#endif /* FILES_H */

