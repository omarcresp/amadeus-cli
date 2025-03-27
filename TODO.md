# TODO

This TODO file outlines the missing parts and potential enhancements for the project based on the requirements specified in PROJECT.md and the current implementation review.

## 1. Input Data Parsing
- [x] **XML Parsing:**
  - [x] Integrate a robust XML parsing library (e.g., TinyXML-2).
  - [x] Implement error handling for malformed XML files.
  - [x] Extract employee details (name, id, department, salary).
- [x] **JSON Parsing:**
  - [x] Integrate a reliable JSON library (e.g., nlohmann/json).
  - [x] Validate JSON structure and handle errors gracefully.
  - [x] Extract employee details.

## 2. Data Processing
- [x] **Average Salary Calculation:**
  - [x] Compute the average salary of all employees.
  - [x] Handle edge cases (e.g., division by zero if no employees).
- [x] **Highest-Paid Employee Identification:**
  - [x] Determine and display the employee with the highest salary along with their details.
- [x] **Employee Sorting:**
  - [x] Sort employees based on their IDs in ascending order.

## 3. Output Reporting
- [x] Implement clear and formatted output for:
  - [x] The average salary.
  - [x] Details of the highest-paid employee.
  - [x] The sorted list of employees by ID.

## 4. Automation & Build System
- [x] **Nix Configuration:**
  - [x] Replace traditional shell scripts with Nix-based build and run configurations.
  - [x] Create a `default.nix` (or equivalent) file to manage dependencies, build, and run the project.
  - [x] Document usage instructions in the README.

## 5. Testing and Error Handling
- [x] **Unit and Integration Tests:**
  - [x] Write tests for both XML and JSON parsing (including malformed input cases).
  - [x] Validate error handling for incorrect file formats and missing files.
- [ ] Consider using a testing framework (e.g., Catch2) for structured tests.

## 6. Documentation and Version Control
- [x] Update README.md with detailed instructions on:
  - [x] Compilation, execution, and testing steps.
  - [x] Using the Nix configuration for building the project.
- [x] Ensure commit messages are descriptive and align with the changes outlined here.

## 7. Additional Enhancements (Optional)
- [x] **Performance Optimization:**
  - [x] Profile and optimize the parsing and data processing routines if needed.
- [x] **Modern C++23 Features:**
  - [x] Refactor code to fully leverage modern C++ features such as structured bindings, ranges, and std::expected for error handling.
- [x] **Exception Handling:**
  - [x] Enhance error messages and integrate robust exception handling throughout the code. 