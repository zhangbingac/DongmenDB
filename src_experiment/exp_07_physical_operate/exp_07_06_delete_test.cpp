//
// Created by maokw on 2020-03-04.
//

#include <cstdio>
#include <gtest/gtest.h>
#include <test/test_stmt_parser.h>
#include <test/test_physical_operate.h>

class DeleteOperateTest : public TestPhysicalOperate {
protected:
    void SetUp() override {
        if (count++ == 0) {
            createDB(dbname);
            createTable();
            insertData();
            ctx = test_db_ctx;
        } else {
            test_db_ctx = ctx;
        }
    }

    void TearDown() override {
        if (count-- == 0) {
            dropDB();
        }
    }

    const char *dbname = "test_demodb";
public:
    static dongmendb_shell_handle_sql_t *ctx;
    static int count;
};

int DeleteOperateTest::count = 0;
dongmendb_shell_handle_sql_t *DeleteOperateTest::ctx = nullptr;

TEST_F(DeleteOperateTest, Test1) {
    EXPECT_EQ(1, delete_("delete student where sname = 'tom simith'"));
}

TEST_F(DeleteOperateTest, Test2) {
    EXPECT_EQ(0, delete_("select * from student where sname = 'tom simith'"));
}

TEST_F(DeleteOperateTest, Test3) {
    EXPECT_EQ(1, delete_("delete student where sno = '2012010102'"));
}

TEST_F(DeleteOperateTest, Test4) {
    EXPECT_EQ(0, delete_("select *  from student where sno = '2012010102'"));
}

TEST_F(DeleteOperateTest, Test5) {
    EXPECT_EQ(1, delete_("delete student  where sname = 'john simith' and ssex='male'"));
}

TEST_F(DeleteOperateTest, Test6) {
    EXPECT_EQ(0, delete_("select *  from student  where sname = 'john simith' and ssex='male'"));
}

TEST_F(DeleteOperateTest, Test7) {
    EXPECT_EQ(2, delete_("delete sc where sno = '2012010103'"));
}

TEST_F(DeleteOperateTest, Test8) {
    EXPECT_EQ(0, delete_("select *  from sc where sno = '2012010103' "));
}

TEST_F(DeleteOperateTest, Test9) {
    EXPECT_EQ(3, delete_("delete sc  where grade >= 80 and cno = 'c003'"));
}

TEST_F(DeleteOperateTest, Test10) {
    EXPECT_EQ(0, delete_("select *  from sc  where grade >= 80 and cno = 'c003'"));
}
