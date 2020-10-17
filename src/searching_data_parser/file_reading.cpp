#include <fstream>
#include <iterator>
#include <exception>
#include <stdexcept>

std::string readFileContent(const std::string& filePath) {
  // Opens input-only file (ifstream) in binary mode.
  std::ifstream in(filePath, std::ios::binary);

  // The file is in a bad state. The error can be retrieved
  //	using the global `errno` in linux (#include <cerrno>).
  if (!in) {
    throw std::runtime_error("could not open file");
  }

  auto content = std::string{std::istreambuf_iterator<char>{in},
                             std::istreambuf_iterator<char>{}};

  return content;
}

void writeFileContent(const std::string& filePath, const std::string& content) {
  // Opens output-only file (ofstream) in binary mode, and truncates all
  //    existing content from the file.
  std::ofstream out(filePath, std::ios::binary | std::ios::trunc);

  // The file is in a bad state.
  if (!out) {
    throw std::runtime_error("error in writing to file.");
  }

  out.write(content.data(), static_cast<std::streamsize>(content.length()));
  if (!out) {
    throw std::runtime_error("error in writing to file.");
  }
}

void appendLineToFile(const std::string& filepath, const std::string& line)
{
    std::ofstream file;
    file.open(filepath, std::ios::out | std::ios::app);
    if (file.fail())
      throw std::runtime_error("could not open file.");

    file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);

    file << line << std::endl;
}
