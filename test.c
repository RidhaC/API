#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <check.h>
#include <sys/stat.h>
#include "ufsext.h"

char *get_file_content(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return NULL;
    }

    struct stat st;
    if (fstat(fd, &st) == -1)
    {
        perror("fstat");
        close(fd);
        return NULL;
    }
    off_t file_size = st.st_size;

    char *buffer = malloc(file_size + 1);
    ssize_t bytes_read = 0;
    ssize_t total_bytes_read = 0;
    while ((bytes_read = read(fd, buffer + total_bytes_read, file_size - total_bytes_read)) > 0)
    {
        total_bytes_read += bytes_read;
    }
    buffer[total_bytes_read] = '\0';

    close(fd);

    return buffer;
}

START_TEST(test_insert)
{
    int fd = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        ck_assert_msg(0, "Failed to create testfile.txt");
    // Initial content
    const char *initial_content = "Hello, World!";
    if (write(fd, initial_content, strlen(initial_content)) == -1)
        ck_assert_msg(0, "Failed to write initial data to testfile.txt");
    close(fd);

    // Insert operation
    fd = open("testfile.txt", O_RDWR);
    if (fd == -1)
        ck_assert_msg(0, "Failed to open testfile.txt");
    const char *insert_text = " INSERTED";
    ck_assert_int_eq(insert(fd, (void *)insert_text, strlen(insert_text), 7), 9);
    close(fd);

    ck_assert_str_eq(get_file_content("testfile.txt"), "Hello,  INSERTEDWorld!");

    if (unlink("testfile.txt") == -1)
        ck_assert_msg(0, "Failed to remove testfile.txt");
}
END_TEST

START_TEST(test_insert1)
{
    int fd = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        ck_assert_msg(0, "Failed to create testfile.txt");
    // Initial content
    const char *initial_content = "Hello, World!";
    if (write(fd, initial_content, strlen(initial_content)) == -1)
        ck_assert_msg(0, "Failed to write initial data to testfile.txt");
    close(fd);

    // Insert operation
    fd = open("testfile.txt", O_RDWR);
    if (fd == -1)
        ck_assert_msg(0, "Failed to open testfile.txt");
    const char *insert_text = "ABCD";
    ck_assert_int_eq(insert(fd, (void *)insert_text, 3, 13),3);
    close(fd);

    ck_assert_str_eq(get_file_content("testfile.txt"), "Hello, World!ABC");

    if (unlink("testfile.txt") == -1)
        ck_assert_msg(0, "Failed to remove testfile.txt");
}
END_TEST

START_TEST(test_insert2)
{
    int fd = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        ck_assert_msg(0, "Failed to create testfile.txt");
    // Initial content
    const char *initial_content = "Hello, World!";
    if (write(fd, initial_content, strlen(initial_content)) == -1)
        ck_assert_msg(0, "Failed to write initial data to testfile.txt");
    close(fd);

    // Insert operation
    fd = open("testfile.txt", O_RDWR);
    if (fd == -1)
        ck_assert_msg(0, "Failed to open testfile.txt");
    const char *insert_text = "ABCD";
    ck_assert_int_eq(insert(fd, (void *)insert_text, 2, 0),2);
    close(fd);

    ck_assert_str_eq(get_file_content("testfile.txt"), "ABHello, World!");

    if (unlink("testfile.txt") == -1)
        ck_assert_msg(0, "Failed to remove testfile.txt");
}
END_TEST

START_TEST(test_delete)
{
    int fd = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        ck_assert_msg(0, "Failed to create testfile.txt");
    // Initial content
    const char *initial_content = "Hello, World!";
    if (write(fd, initial_content, strlen(initial_content)) == -1)
        ck_assert_msg(0, "Failed to write initial data to testfile.txt");
    close(fd);

    // Delete operation
    fd = open("testfile.txt", O_RDWR);
    if (fd == -1)
        ck_assert_msg(0, "Failed to open testfile.txt");
    ck_assert_int_eq(delete (fd, 5, 7),5);
    close(fd);

    ck_assert_str_eq(get_file_content("testfile.txt"), "Hello, !");

    if (unlink("testfile.txt") == -1)
        ck_assert_msg(0, "Failed to remove testfile.txt");
}
END_TEST

START_TEST(test_delete1)
{
    int fd = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        ck_assert_msg(0, "Failed to create testfile.txt");
    // Initial content
    const char *initial_content = "Hello, World!";
    if (write(fd, initial_content, strlen(initial_content)) == -1)
        ck_assert_msg(0, "Failed to write initial data to testfile.txt");
    close(fd);

    // Delete operation
    fd = open("testfile.txt", O_RDWR);
    if (fd == -1)
        ck_assert_msg(0, "Failed to open testfile.txt");
    ck_assert_int_eq(delete (fd, 2, 0), 2);
    close(fd);

    ck_assert_str_eq(get_file_content("testfile.txt"), "llo, World!");

    if (unlink("testfile.txt") == -1)
        ck_assert_msg(0, "Failed to remove testfile.txt");
}
END_TEST

START_TEST(test_delete2)
{
    int fd = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        ck_assert_msg(0, "Failed to create testfile.txt");
    // Initial content
    const char *initial_content = "Hello, World!";
    if (write(fd, initial_content, strlen(initial_content)) == -1)
        ck_assert_msg(0, "Failed to write initial data to testfile.txt");
    close(fd);

    // Delete operation
    fd = open("testfile.txt", O_RDWR);
    if (fd == -1)
        ck_assert_msg(0, "Failed to open testfile.txt");
    ck_assert_int_eq(delete (fd, 5, 7), 5);
    close(fd);

    ck_assert_str_eq(get_file_content("testfile.txt"), "Hello, !");

    if (unlink("testfile.txt") == -1)
        ck_assert_msg(0, "Failed to remove testfile.txt");
}
END_TEST

START_TEST(test_extract)
{
    int fd = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        ck_assert_msg(0, "Failed to create testfile.txt");
    // Initial content
    const char *initial_content = "Hello, World!";
    if (write(fd, initial_content, strlen(initial_content)) == -1)
        ck_assert_msg(0, "Failed to write initial data to testfile.txt");
    close(fd);

    // Extract operation
    fd = open("testfile.txt", O_RDWR);
    if (fd == -1)
        ck_assert_msg(0, "Failed to open testfile.txt");
    char extract_buf[6];
    ck_assert_int_eq(extract(fd, extract_buf, 5, 7), 5);
    close(fd);

    extract_buf[5] = '\0';
    ck_assert_str_eq(extract_buf, "World");
    ck_assert_str_eq(get_file_content("testfile.txt"), "Hello, !");

    if (unlink("testfile.txt") == -1)
        ck_assert_msg(0, "Failed to remove testfile.txt");
}
END_TEST

START_TEST(test_extract1)
{
    int fd = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        ck_assert_msg(0, "Failed to create testfile.txt");
    // Initial content
    const char *initial_content = "Hello, World!";
    if (write(fd, initial_content, strlen(initial_content)) == -1)
        ck_assert_msg(0, "Failed to write initial data to testfile.txt");
    close(fd);

    // Extract operation
    fd = open("testfile.txt", O_RDWR);
    if (fd == -1)
        ck_assert_msg(0, "Failed to open testfile.txt");
    char extract_buf[4];
    ck_assert_int_eq(extract(fd, extract_buf, 3, 0), 3);
    close(fd);

    extract_buf[3] = '\0';
    ck_assert_str_eq(extract_buf, "Hel");
    ck_assert_str_eq(get_file_content("testfile.txt"), "lo, World!");

    if (unlink("testfile.txt") == -1)
        ck_assert_msg(0, "Failed to remove testfile.txt");
}
END_TEST

START_TEST(test_extract2)
{
    int fd = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        ck_assert_msg(0, "Failed to create testfile.txt");
    // Initial content
    const char *initial_content = "Hello, World!";
    if (write(fd, initial_content, strlen(initial_content)) == -1)
        ck_assert_msg(0, "Failed to write initial data to testfile.txt");
    close(fd);

    // Extract operation
    fd = open("testfile.txt", O_RDWR);
    if (fd == -1)
        ck_assert_msg(0, "Failed to open testfile.txt");
    char extract_buf[3];
    ck_assert_int_eq(extract(fd, extract_buf, 2, 11), 2);
    close(fd);

    extract_buf[2] = '\0';
    ck_assert_str_eq(extract_buf, "d!");
    ck_assert_str_eq(get_file_content("testfile.txt"), "Hello, Worl");

    if (unlink("testfile.txt") == -1)
        ck_assert_msg(0, "Failed to remove testfile.txt");
}
END_TEST

START_TEST(test_inter)
{
    int fd = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        ck_assert_msg(0, "Failed to create testfile.txt");
    // Initial content
    const char *initial_content = "Hello, World!";
    if (write(fd, initial_content, strlen(initial_content)) == -1)
        ck_assert_msg(0, "Failed to write initial data to testfile.txt");
    close(fd);

    // Insert operation
    fd = open("testfile.txt", O_RDWR);
    if (fd == -1)
        ck_assert_msg(0, "Failed to open testfile.txt");
    const char *insert_text = " INSERTED";
    ck_assert_int_eq(insert(fd, (void *)insert_text, strlen(insert_text), 7), 9);

    ck_assert_int_eq(delete (fd, 5, 7), 5);

    char extract_buf[5];
    ck_assert_int_eq(extract(fd, extract_buf, 5, 7), 5);


    if (unlink("testfile.txt") == -1)
        ck_assert_msg(0, "Failed to remove testfile.txt");
}
END_TEST

START_TEST(test_error)
{
    int fd = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        ck_assert_msg(0, "Failed to create testfile.txt");
    close(fd);

    // Insert operation
    fd = open("testfile.txt", O_RDWR);
    if (fd == -1)
        ck_assert_msg(0, "Failed to open testfile.txt");
    const char *insert_text = " INSERTED";
    ck_assert_int_eq(insert(fd, (void *)insert_text, strlen(insert_text), 7), -1);

    if (unlink("testfile.txt") == -1)
        ck_assert_msg(0, "Failed to remove testfile.txt");
}
END_TEST

START_TEST(test_error1)
{
    int fd = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        ck_assert_msg(0, "Failed to create testfile.txt");
    close(fd);

    // Insert operation
    fd = open("testfile.txt", O_RDWR);
    if (fd == -1)
        ck_assert_msg(0, "Failed to open testfile.txt");
    const char *insert_text = " INSERTED";
    ck_assert_int_eq(delete (fd, 2, 10), -1);

    if (unlink("testfile.txt") == -1)
        ck_assert_msg(0, "Failed to remove testfile.txt");
}
END_TEST

START_TEST(test_error2)
{
    int fd = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        ck_assert_msg(0, "Failed to create testfile.txt");
    close(fd);

    // Insert operation
    fd = open("testfile.txt", O_RDWR);
    if (fd == -1)
        ck_assert_msg(0, "Failed to open testfile.txt");
    const char *insert_text = " INSERTED";
    char extract_buf[5];
    ck_assert_int_eq(extract(fd, extract_buf, -2, 3), -1);

    if (unlink("testfile.txt") == -1)
        ck_assert_msg(0, "Failed to remove testfile.txt");
}
END_TEST

START_TEST(test_error3)
{
    int fd = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        ck_assert_msg(0, "Failed to create testfile.txt");
    close(fd);

    // Insert operation
    fd = open("testfile.txt", O_RDWR);
    if (fd == -1)
        ck_assert_msg(0, "Failed to open testfile.txt");
    const char *insert_text = " INSERTED";

    ck_assert_int_eq(insert(fd, (void *)insert_text, 0, 2), -1);

    if (unlink("testfile.txt") == -1)
        ck_assert_msg(0, "Failed to remove testfile.txt");
}
END_TEST

Suite *interp_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("UFSEXT");

    /* Core test case */
    tc_core = tcase_create("tests");

    tcase_add_test(tc_core, test_insert);
    tcase_add_test(tc_core, test_insert1);
    tcase_add_test(tc_core, test_insert2);
    tcase_add_test(tc_core, test_delete);
    tcase_add_test(tc_core, test_delete1);
    tcase_add_test(tc_core, test_delete2);
    tcase_add_test(tc_core, test_extract);
    tcase_add_test(tc_core, test_extract1);
    tcase_add_test(tc_core, test_extract2);
    tcase_add_test(tc_core, test_inter);
    tcase_add_test(tc_core, test_error);
    tcase_add_test(tc_core, test_error1);
    tcase_add_test(tc_core, test_error2);
    tcase_add_test(tc_core, test_error3);

    suite_add_tcase(s, tc_core);
    return s;
}

int main()
{

    SRunner *sr = srunner_create(interp_suite());

    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return failed;
}
