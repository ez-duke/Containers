#include "test_containers.h"

using namespace s21;

TEST(test_map, constructorDefault) {
  Map<std::string, std::string> map_empty;

  EXPECT_EQ(map_empty.Size(), 0);
}

TEST(test_map, constructorInitializer_list) {
  Map<std::string, std::string> map_initializer_list(
      {{"apple", "manzana"}, {"strawberry", "fresa"}, {"orange", "naranja"}});

  EXPECT_EQ(map_initializer_list.Size(), 3);
  EXPECT_EQ(map_initializer_list.at("apple"), "manzana");
  EXPECT_EQ(map_initializer_list.at("strawberry"), "fresa");
  EXPECT_EQ(map_initializer_list.at("orange"), "naranja");
}

TEST(test_map, constructorCopy) {
  Map<std::string, std::string> map_initializer_list(
      {{"apple", "manzana"}, {"strawberry", "fresa"}, {"orange", "naranja"}});
  Map<std::string, std::string> map_copy(map_initializer_list);

  EXPECT_EQ(map_initializer_list.Size(), map_copy.Size());
  EXPECT_EQ(map_copy.at("apple"), "manzana");
  EXPECT_EQ(map_copy.at("strawberry"), "fresa");
  EXPECT_EQ(map_copy.at("orange"), "naranja");
}

TEST(test_map, constructorMove) {
  Map<std::string, std::string> map_initializer_list(
      {{"apple", "manzana"}, {"strawberry", "fresa"}, {"orange", "naranja"}});
  Map<std::string, std::string> map_move(std::move(map_initializer_list));

  EXPECT_EQ(map_initializer_list.Size(), 0);
  EXPECT_EQ(map_move.Size(), 3);
  EXPECT_EQ(map_move.at("apple"), "manzana");
  EXPECT_EQ(map_move.at("strawberry"), "fresa");
  EXPECT_EQ(map_move.at("orange"), "naranja");
}

TEST(test_map, operatorAssign) {
  Map<std::string, std::string> map_initializer_list(
      {{"apple", "manzana"}, {"strawberry", "fresa"}, {"orange", "naranja"}});
  Map<std::string, std::string> map_operatorAssign =
      std::move(map_initializer_list);

  EXPECT_EQ(map_initializer_list.Size(), 0);
  EXPECT_EQ(map_operatorAssign.Size(), 3);
  EXPECT_EQ(map_operatorAssign.at("apple"), "manzana");
  EXPECT_EQ(map_operatorAssign.at("strawberry"), "fresa");
  EXPECT_EQ(map_operatorAssign.at("orange"), "naranja");
}

TEST(test_map, at) {
  Map<std::string, std::string> map_initializer_list(
      {{"apple", "manzana"}, {"strawberry", "fresa"}, {"orange", "naranja"}});

  EXPECT_EQ(map_initializer_list.at("apple"), "manzana");
  EXPECT_EQ(map_initializer_list.at("strawberry"), "fresa");
  EXPECT_EQ(map_initializer_list.at("orange"), "naranja");
  EXPECT_THROW(map_initializer_list.at("banana"), std::out_of_range);
}

TEST(test_map, indexOperator) {
  Map<std::string, std::string> map_initializer_list(
      {{"apple", "manzana"}, {"strawberry", "fresa"}, {"orange", "naranja"}});
  map_initializer_list["new"] = "nuevo";

  EXPECT_EQ(map_initializer_list.at("new"), "nuevo");
}

TEST(test_map, begin) {
  Map<std::string, std::string> map_initializer_list(
      {{"apple", "manzana"}, {"strawberry", "fresa"}, {"orange", "naranja"}});
  EXPECT_EQ(map_initializer_list.find("apple"), map_initializer_list.begin());
}

TEST(test_map, end) {
  Map<std::string, std::string> map_initializer_list(
      {{"apple", "manzana"}, {"strawberry", "fresa"}, {"orange", "naranja"}});
  EXPECT_EQ(map_initializer_list.find("strawberry"),
            map_initializer_list.end());

  Map<int, int> map_empty;
  EXPECT_EQ(map_empty.begin(), map_empty.end());
}

TEST(test_map, empty) {
  Map<std::string, std::string> map_initializer_list(
      {{"apple", "manzana"}, {"strawberry", "fresa"}, {"orange", "naranja"}});
  Map<std::string, std::string> map_empty;

  EXPECT_FALSE(map_initializer_list.empty());
  EXPECT_TRUE(map_empty.empty());
}

TEST(test_map, Size) {
  Map<std::string, std::string> map_initializer_list(
      {{"apple", "manzana"}, {"strawberry", "fresa"}, {"orange", "naranja"}});

  EXPECT_EQ(map_initializer_list.Size(), 3);
}

TEST(test_map, clear) {
  Map<std::string, std::string> map_initializer_list(
      {{"apple", "manzana"}, {"strawberry", "fresa"}, {"orange", "naranja"}});
  map_initializer_list.clear();

  EXPECT_EQ(map_initializer_list.Size(), 0);
}

TEST(test_map, insertValue) {
  Map<std::string, std::string> map_initializer_list(
      {{"apple", "manzana"}, {"strawberry", "fresa"}, {"orange", "naranja"}});
  map_initializer_list.insert("new", "nuevo");

  EXPECT_EQ(map_initializer_list.Size(), 4);
  EXPECT_EQ(map_initializer_list.at("new"), "nuevo");
}

TEST(test_map, insertKeyObj) {
  Map<std::string, std::string> map_initializer_list(
      {{"apple", "manzana"}, {"strawberry", "fresa"}, {"orange", "naranja"}});
  std::string key = "key";
  std::string value = "value";
  map_initializer_list.insert(key, value);

  EXPECT_EQ(map_initializer_list.Size(), 4);
  EXPECT_EQ(map_initializer_list.at("key"), "value");
}

TEST(test_map, insert_or_assign) {
  Map<std::string, std::string> map_initializer_list(
      {{"apple", "manzana"}, {"strawberry", "fresa"}, {"orange", "naranja"}});
  std::string key = "key";
  std::string value = "value";
  map_initializer_list.insert(key, value);
  std::string value2 = "value2";
  map_initializer_list.insert_or_assign(key, value2);

  EXPECT_EQ(map_initializer_list.at("key"), "value2");
}

TEST(test_map, erase) {
  Map<std::string, std::string> map_initializer_list(
      {{"apple", "manzana"}, {"strawberry", "fresa"}, {"orange", "naranja"}});
  map_initializer_list.erase(map_initializer_list.begin());

  EXPECT_THROW(map_initializer_list.at("apple"), std::out_of_range);
}

TEST(test_map, swap) {
  Map<std::string, std::string> map_swap1({{"sw1", "ap1"}, {"ap1", "sw1"}});
  Map<std::string, std::string> map_swap2({{"sw2", "ap2"}});
  map_swap1.swap(map_swap2);

  EXPECT_EQ(map_swap1.Size(), 1);
  EXPECT_EQ(map_swap2.Size(), 2);
  EXPECT_EQ(map_swap1.at("sw2"), "ap2");
  EXPECT_EQ(map_swap2.at("sw1"), "ap1");
}

TEST(test_map, merge) {
  Map<std::string, std::string> map_merge1({{"sw1", "ap1"}, {"ap1", "sw1"}});
  Map<std::string, std::string> map_merge2({{"sw2", "ap2"}});
  map_merge1.merge(map_merge2);

  EXPECT_EQ(map_merge1.Size(), 3);
  EXPECT_EQ(map_merge1.at("sw2"), "ap2");
  EXPECT_EQ(map_merge1.at("sw1"), "ap1");
  EXPECT_EQ(map_merge1.at("ap1"), "sw1");
}

TEST(test_map, contains) {
  Map<std::string, std::string> map_initializer_list(
      {{"apple", "manzana"}, {"strawberry", "fresa"}, {"orange", "naranja"}});

  EXPECT_TRUE(map_initializer_list.contains("apple"));
  EXPECT_FALSE(map_initializer_list.contains("banana"));
}

TEST(test_map, insert_many) {
  Map<std::string, std::string> map_insert_many;
  map_insert_many.insert_many(
      std::pair<std::string, std::string>("apple", "manzana"),
      std::pair<std::string, std::string>("strawberry", "fresa"),
      std::pair<std::string, std::string>("orange", "naranja"));

  EXPECT_EQ(map_insert_many.Size(), 3);
  EXPECT_EQ(map_insert_many.at("apple"), "manzana");
  EXPECT_EQ(map_insert_many.at("strawberry"), "fresa");
  EXPECT_EQ(map_insert_many.at("orange"), "naranja");
}
