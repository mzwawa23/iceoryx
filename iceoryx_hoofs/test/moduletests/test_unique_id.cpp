#include <gtest/gtest.h>
#include <cstdio>
#include <stdexcept>

// Assuming IOException is defined somewhere
class IOException : public std::runtime_error {
public:
    IOException() : std::runtime_error("IO Exception") {}
};

int* readIntegerArray(FILE* file, int* pSize);

TEST(ReadIntegerArrayTest, ValidInput) {
    const char* testFileName = "testfile.txt";
    FILE* file = fopen(testFileName, "w+");
    fprintf(file, "3\n1 2 3\n");
    rewind(file);

    int size;
    int* result = readIntegerArray(file, &size);

    ASSERT_EQ(size, 3);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 2);
    ASSERT_EQ(result[2], 3);

    delete[] result;
    fclose(file);
    remove(testFileName);
}

TEST(ReadIntegerArrayTest, EmptyFile) {
    const char* testFileName = "emptyfile.txt";
    FILE* file = fopen(testFileName, "w+");
    rewind(file);

    int size;
    EXPECT_THROW(readIntegerArray(file, &size), IOException);

    fclose(file);
    remove(testFileName);
}

TEST(ReadIntegerArrayTest, IncompleteData) {
    const char* testFileName = "incompletefile.txt";
    FILE* file = fopen(testFileName, "w+");
    fprintf(file, "3\n1 2\n");
    rewind(file);

    int size;
    EXPECT_THROW(readIntegerArray(file, &size), IOException);

    fclose(file);
    remove(testFileName);
}

TEST(ReadIntegerArrayTest, InvalidSize) {
    const char* testFileName = "invalidsizefile.txt";
    FILE* file = fopen(testFileName, "w+");
    fprintf(file, "invalid\n");
    rewind(file);

    int size;
    EXPECT_THROW(readIntegerArray(file, &size), IOException);

    fclose(file);
    remove(testFileName);
}

/*
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/