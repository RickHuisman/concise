#include "gtest/gtest.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vm/vm.h>

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

void execute(std::string source) {
  VM vm;

  std::stringstream buffer;
  vm.interpret(source);

  std::cout << buffer.rdbuf();
}

void run_test_file(std::string path) {
  std::ifstream ifs(path);
  std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

  execute(content);
}

std::vector<std::string> collect_test_file_paths() {
  std::vector<std::string> paths;

  std::string path = "../../test/tests";
  for (const auto &entry: recursive_directory_iterator(path)) {
    if (entry.is_regular_file()) {
      paths.push_back(entry.path());
    }
  }

  return paths;
}

TEST(language_tests, run_test_suite) {
  auto test_paths = collect_test_file_paths();

  for (auto path : test_paths) {
    run_test_file(path);
  }
}
