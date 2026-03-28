# Text & Code Plagiarism Detection System in C

## Overview

This project implements a plagiarism detection system in C that compares a base file with multiple input files and calculates similarity percentage. The system works for both plain text and source code by analyzing content line-by-line and comparing structural similarity using token-based analysis.

---

## Objective

The objective of this project is to demonstrate the application of fundamental data structures such as stacks, hash tables, linked lists, and tries in solving a real-world problem of plagiarism detection.

---

## Features

- Line-by-line comparison of files  
- Token-based similarity detection (not exact string matching)  
- Works for both text documents and source code  
- Ignores formatting differences (spaces, case, punctuation)  
- Supports multiple file comparisons  
- Uses Jaccard similarity for similarity calculation  

---

## Data Structures Used

- **Stack** → builds tokens from characters  
- **Trie** → stores tokens structurally  
- **Hash Table** → stores token frequency  
- **Linked List** → handles hash collisions  
- **Arrays** → used for storage and processing  

---

## Working Principle

1. Read input files line by line  
2. Normalize text (lowercase, remove unwanted characters)  
3. Convert each line into tokens  
4. Store tokens using hash tables and trie  
5. Compare token sets using Jaccard similarity  
6. Count matching lines  
7. Compute final plagiarism percentage  

---

## Similarity Formula

J(A,B) = |A ∩ B| / |A ∪ B|

---

## How to Compile

Open terminal in your project folder and run:

```bash
gcc main.c -o plagiarism
