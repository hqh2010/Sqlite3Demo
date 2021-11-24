#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sqlite3.h>

// 需要安装libsqlite3-dev
// g++ main.cpp -g -I/usr/include -lsqlite3 -o main

int main(int argc, char **argv)
{
    sqlite3 *db = NULL;
    int row = 0;
    int column = 0;
    char *errMsg = NULL;
    // 二维数组存放结果
    char **asResult = NULL;
    char curpath[512] = {'\0'};
    getcwd(curpath, 512);
    // 打开数据库
    int ret = sqlite3_open("userinfo.db", &db);
    if (ret != SQLITE_OK) {
        fprintf(stdout, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    } else {
        printf("open sqlite3 database successfully!\n");
    }

    char *sql = "CREATE TABLE IF NOT EXISTS student(\
         ID INTEGER PRIMARY KEY AUTOINCREMENT,\
         name VARCHAR(32) NOT NULL,\
         sex CHAR(10),\
         score INTEGER\
         );";
    ret = sqlite3_exec(db, sql, NULL, NULL, &errMsg);
    if (ret != SQLITE_OK) {
        printf("sqlite3_exec %s err, msg:%s\n", sql, errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return -1;
    }

    // 插入数据
    // ID 自动生成以便可以多次执行
    // sql = "INSERT INTO student VALUES(1,'zhangsan', '男','78');";
    sql = "INSERT INTO student(name,sex,score) VALUES('zhangsan', '男','78');";
    ret = sqlite3_exec(db, sql, NULL, NULL, &errMsg);
    if (ret != SQLITE_OK) {
        printf("sqlite3_exec %s err, msg:%s\n", sql, errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return -1;
    }

    sql = "INSERT INTO student(name,sex,score) VALUES('lili', '女','80');";
    ret = sqlite3_exec(db, sql, NULL, NULL, &errMsg);
    if (ret != SQLITE_OK) {
        printf("sqlite3_exec %s err, msg:%s\n", sql, errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return -1;
    }

    sql = "INSERT INTO student(name,sex,score) VALUES('wangwu', '男','85');";
    ret = sqlite3_exec(db, sql, NULL, NULL, &errMsg);
    if (ret != SQLITE_OK) {
        printf("sqlite3_exec %s err, msg:%s\n", sql, errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return -1;
    }

    sql = "INSERT INTO student(name,sex,score) VALUES('lilei', '男','90');";
    ret = sqlite3_exec(db, sql, NULL, NULL, &errMsg);
    if (ret != SQLITE_OK) {
        printf("sqlite3_exec %s err, msg:%s\n", sql, errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return -1;
    }

    // 更新数据
    sql = "update student set score=81,sex='女' where name='wangwu';";
    ret = sqlite3_exec(db, sql, NULL, NULL, &errMsg);
    if (ret != SQLITE_OK) {
        printf("sqlite3_exec %s err, msg:%s\n", sql, errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return -1;
    }

    // 查询数据集，也可以使用回调函数查询结果
    sql = "select *from student;";
    ret = sqlite3_get_table(db, sql, &asResult, &row, &column, &errMsg);
    if (ret != SQLITE_OK) {
        printf("sqlite3_exec %s err, msg:%s\n", sql, errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return -1;
    }

    printf("查询结果数据集大小: row = %d, column = %d\n", row, column);
    printf("the result is:\n");
    for (int i = 0; i < (row + 1) * column; i++) {
        // printf("asResult[%d] = %s\n", i, asResult[i]);
        printf("%s  ", asResult[i]);
        if (((i + 1) % column == 0) && (i != 0)) {
            printf("\n");
        }
    }
    // 查询完毕后释放内存
    sqlite3_free_table(asResult);

    // 删除某个特定的数据
    sql = "delete from student where name = 'lilei';";
    ret = sqlite3_exec(db, sql, NULL, NULL, &errMsg);
    if (ret != SQLITE_OK) {
        printf("sqlite3_exec %s err, msg:%s\n", sql, errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return -1;
    }

    // 查询删除后的数据
    sql = "SELECT * FROM student;";
    ret = sqlite3_get_table(db, sql, &asResult, &row, &column, &errMsg);
    if (ret != SQLITE_OK) {
        printf("sqlite3_exec %s err, msg:%s\n", sql, errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return -1;
    }
    printf("row = %d, column = %d\n", row, column);
    printf("After deleting , the result is : \n");
    for (int i = 0; i < (row + 1) * column; i++) {
        // printf("asResult[%d] = %s\n", i, asResult[i]);
        printf("%s  ", asResult[i]);
        if (((i + 1) % column == 0) && (i != 0)) {
            printf("\n");
        }
    }
    sqlite3_free_table(asResult);
    sqlite3_close(db);
    return 0;
}