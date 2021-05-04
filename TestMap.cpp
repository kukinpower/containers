#include "TestRunner.h"
#include <array>
#include "TreePrinter.h"

namespace TestMap {

void TestEmpty(TestRunner const &tr) {
  std::map<std::string, int> m;
  ft::Map<std::string, int> fm;
  Assert(fm.empty() == m.empty(), tr.hintMessage("empty"));
}

void TestMaxSize(TestRunner const &tr) {
  std::map<std::string, int> m;
  ft::Map<std::string, int> fm;

//  std::cout << "m.max_size(): " << m.max_size() << " fm.max_size(): " << fm.max_size() << std::endl;
//  if (m.max_size() > fm.max_size()) {
//    std::cout << "m.max_size() - fm.max_size() res: " << m.max_size() - fm.max_size() << std::endl;
//  } else {
//    std::cout << "fm.max_size() - m.max_size() res: " << fm.max_size() - m.max_size() << std::endl;
//  }
  Assert((fm.max_size() > 200000000000000000 && m.max_size() > 200000000000000000) ||
      (fm.max_size() <= 200000000000000000 && m.max_size() <= 200000000000000000), tr.hintMessage("max_size"));
}

void TestSize(TestRunner const &tr) {
  std::map<std::string, int> m;
  ft::Map<std::string, int> fm;
  Assert(fm.size() == m.size(), tr.hintMessage("test empty size"));

  m["one"] = 1;
  m["two"] = 2;

  fm["one"] = 1;
  fm["two"] = 2;

  Assert(fm.size() == m.size(), tr.hintMessage("test size"));
}

void TestAdd(TestRunner const &tr) {
  std::map<std::string, int> m;
  ft::Map<std::string, int> fm;

  m["one"] = 1;
  m["two"] = 2;

  fm["one"] = 1;
  fm["two"] = 2;

  AssertEqual(fm, m, tr.hintMessage("add, operator[]"));
}

void TestConstructorsConst(std::map<int, int> const &m, ft::Map<int, int> const &fm, TestRunner const &tr) {
  std::map<int, int> m2(m.begin(), m.end());
  ft::Map<int, int> fm2(fm.begin(), fm.end());
  AssertEqual(fm2, m2, tr.hintMessage("range constructor const"));

  std::map<int, int> m3(m2.begin(), m2.end());
  ft::Map<int, int> fm3(fm2.begin(), fm2.end());
  AssertEqual(fm3, m3, tr.hintMessage("copy constructor const"));
}

void TestConstructors(TestRunner const &tr) {
  std::map<int, int> m;
  ft::Map<int, int> fm;
  AssertEqual(fm, m, tr.hintMessage("empty constructor"));

  srand (time(NULL));

  for (int i = 0; i < 20; ++i) {
    int r = rand() % 100 + 1;
    m.insert(std::make_pair(r, r));
    fm.insert(std::make_pair(r, r));
  }

  std::map<int, int> m2(m.begin(), m.end());
  ft::Map<int, int> fm2(fm.begin(), fm.end());
  AssertEqual(fm2, m2, tr.hintMessage("range constructor"));

  std::map<int, int> m3(m2.begin(), m2.end());
  ft::Map<int, int> fm3(fm2.begin(), fm2.end());
  AssertEqual(fm3, m3, tr.hintMessage("copy constructor"));

  TestConstructorsConst(m, fm, tr);
}

void TestTestAssignationOperatorConst(std::map<int, int> const &m, ft::Map<int, int> const &fm, TestRunner const &tr) {
  std::map<int, int> m2 = m;
  ft::Map<int, int> fm2 = fm;
  AssertEqual(fm2, m2, tr.hintMessage("operator= const"));
}

void TestAssignationOperator(TestRunner const &tr) {
  std::map<int, int> m;
  ft::Map<int, int> fm;

  srand (time(NULL));

  for (int i = 0; i < 20; ++i) {
    int r = rand() % 100 + 1;
    m.insert(std::make_pair(r, r));
    fm.insert(std::make_pair(r, r));
  }

  std::map<int, int> m2 = m;
  ft::Map<int, int> fm2 = fm;
  AssertEqual(fm2, m2, tr.hintMessage("operator="));

  TestTestAssignationOperatorConst(m, fm, tr);
}

void TestConstIterator(std::map<int, int> const &m, ft::Map<int, int> const &fm, TestRunner const &tr) {
  auto it = m.begin();
  auto fit = fm.begin();

  for (; it != m.end() && fit != fm.end(); ++it, ++fit) {
    Assert(it->first == fit->first && it->second == fit->second,
           tr.hintMessage("iterator"));
  }
}

void TestIterator(TestRunner const &tr) {
  std::map<int, int> m;
  ft::Map<int, int> fm;

  srand (time(NULL));

  for (int i = 0; i < 20; ++i) {
    int r = rand() % 100 + 1;
    m.insert(std::make_pair(r, r));
    fm.insert(std::make_pair(r, r));
  }

  auto it = m.begin();
  auto fit = fm.begin();

  for (; it != m.end() && fit != fm.end(); ++it, ++fit) {
    Assert(it->first == fit->first && it->second == fit->second,
           tr.hintMessage("iterator"));
  }

  TestConstIterator(m, fm, tr);
}

void TestConstReverseIterator(std::map<int, int> const &m, ft::Map<int, int> const &fm, TestRunner const &tr) {
  auto it = m.rbegin();
  auto fit = fm.rbegin();

  for (; it != m.rend() && fit != fm.rend(); ++it, ++fit) {
    Assert(it->first == fit->first && it->second == fit->second,
           tr.hintMessage("iterator"));
  }
}

void TestReverseIterator(TestRunner const &tr) {
  std::map<int, int> m;
  ft::Map<int, int> fm;

  srand (time(NULL));

  for (int i = 0; i < 20; ++i) {
    int r = rand() % 100 + 1;
    m.insert(std::make_pair(r, r));
    fm.insert(std::make_pair(r, r));
  }

  auto it = m.rbegin();
  auto fit = fm.rbegin();

  for (; it != m.rend() && fit != fm.rend(); ++it, ++fit) {
    Assert(it->first == fit->first && it->second == fit->second,
           tr.hintMessage("iterator"));
  }

  TestConstReverseIterator(m, fm, tr);
}

void TestInsert(TestRunner const &tr) {
  std::map<int, int> m;
  ft::Map<int, int> fm;

  for (int i = 0; i < 20; ++i) {
    int r = rand() % 100 + 1;
    m.insert(std::make_pair(r, r));
    fm.insert(std::make_pair(r, r));
  }
  AssertEqual(m, fm, tr.hintMessage("insert single element"));

  auto it = m.begin();
  auto fit = fm.begin();

  for (int i = 0;
        i < 10 && it != m.end() && fit != fm.end();
        ++i, ++it, ++fit) {
  }

  int r = rand() % 100 + 1;
  m.insert(it, std::make_pair(r, r));
  fm.insert(fit, std::make_pair(r, r));
  AssertEqual(m, fm, tr.hintMessage("insert with hint"));

  std::map<int, int> m2;
  ft::Map<int, int> fm2;
  m2.insert(it, m.end());
  fm2.insert(fit, fm.end());
  AssertEqual(m2, fm2, tr.hintMessage("insert range"));
}

void TestAll() {
  TestRunner tr("Map");

  tr.RunTest(TestAdd, "TestAdd");
  tr.RunTest(TestEmpty, "TestEmpty");
  tr.RunTest(TestSize, "TestSize");
  tr.RunTest(TestMaxSize, "TestMaxSize");
  tr.RunTest(TestConstructors, "TestConstructors");
  tr.RunTest(TestAssignationOperator, "TestAssignationOperator");
  tr.RunTest(TestIterator, "TestIterator");
  tr.RunTest(TestReverseIterator, "TestReverseIterator");
  tr.RunTest(TestInsert, "TestInsert");

}
}
