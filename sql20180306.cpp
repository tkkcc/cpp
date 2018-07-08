/*
 * 20180306 bilabila
 * sql homework 1
 * simple CRUD using boost
 *
 */

#include <iostream>
//#include <unordered_map>
#include <map>
#include <vector>
#include <fstream>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
//#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/algorithm/string/predicate.hpp>


typedef std::map<std::string, std::string> record_type;
typedef std::vector<std::map<std::string, std::string>> records_type;

class sql {
    const std::string sql_file = "sql.bin";

    records_type read_records() {
        records_type all_records;
        try {
            std::ifstream fin(sql_file, std::ios::binary);
            boost::archive::binary_iarchive iarch(fin);
            iarch >> all_records;
        } catch (std::exception &err) {}
        return all_records;
    }

    void write_records(records_type &all_records) {
        std::ofstream fout(sql_file, std::ios::binary);
        boost::archive::binary_oarchive oarch(fout);
        oarch << all_records;
    }

public:
    //remove the sql file
    void clear_sql() {
        remove(sql_file.c_str());
    }

    static void print_records(records_type &records) {
        int index = 0;
        for (auto &item:records) {
            std::cout << index++ << "  ";
            for (auto entry = item.begin(); entry != item.end(); ++entry) {
                std::cout << entry->first << ":" << entry->second << (std::next(entry) != item.end() ? ",\t" : "\n");
            }
        }
    }

    void print() {
        records_type all_records = read_records();
        print_records(all_records);
    }

    void add(records_type &records) {
        records_type all_records = read_records();
        //append to exist data
        all_records.insert(all_records.end(), records.begin(), records.end());
        write_records(all_records);
    }

    template<typename L>
    void del(L filter) {
        auto all_records = read_records();
        records_type results;
        all_records.erase(std::remove_if(all_records.begin(), all_records.end(), filter), all_records.end());
        write_records(all_records);
    }

    template<typename L>
    records_type find(L filter) {
        auto all_records = read_records();
        records_type results;
        auto it = std::copy_if(all_records.begin(), all_records.end(), std::back_inserter(results), filter);
        return results;
    }
};

int main() {
    sql s;
    //debug clear data
    //std::cout << "\n===========重建数据库\n\n";
    //s.clear_sql();
    //插入9条记录
    std::cout << "\n===========插入多条记录\n";
    records_type records_add;
    records_add.insert(records_add.end(), {
            record_type({{"班级", "981101"},
                         {"课程", "数据库"},
                         {"教师", "李四"},
                         {"学期", "98秋"},
                         {"学号", "98110101"},
                         {"姓名", "张三"},
                         {"成绩", "99"}}),
            record_type({{"班级", "981101"},
                         {"课程", "数据库"},
                         {"教师", "李四"},
                         {"学期", "98秋"},
                         {"学号", "98110102"},
                         {"姓名", "张四"},
                         {"成绩", "59"}}),
            record_type({{"班级", "981102"},
                         {"课程", "计算机"},
                         {"教师", "李四"},
                         {"学期", "98秋"},
                         {"学号", "98110202"},
                         {"姓名", "王一一"},
                         {"成绩", "60"}}),
            record_type({{"班级", "981101"},
                         {"课程", "计算机"},
                         {"教师", "李四"},
                         {"学期", "98秋"},
                         {"学号", "98110203"},
                         {"姓名", "王物"},
                         {"成绩", "30"}}),
            record_type({{"班级", "981101"},
                         {"课程", "数据库"},
                         {"教师", "2233"},
                         {"学期", "98秋"},
                         {"学号", "98110203"},
                         {"姓名", "王小博"},
                         {"成绩", "10"}})
    });
    s.add(records_add);
    s.print();

    //查找 数据库不及格的所有记录
    std::cout << "\n===========查找数据库不及格所有记录\n";
    auto filter_find = [](record_type &record) -> bool {
        return record["课程"] == "数据库" && stoi(record["成绩"]) < 60;
    };
    auto results = s.find(filter_find);
    sql::print_records(results);

    //删除 王姓同学的所有记录
    std::cout << "\n===========删除王姓同学所有记录\n";
    auto filter_del = [](record_type &record) -> bool {
        return boost::starts_with(record["姓名"], "王");
    };
    s.del(filter_del);
    s.print();
    return 0;
}