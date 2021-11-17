#ifndef CASH_OVERFLOW_CATEGORY_HPP
#define CASH_OVERFLOW_CATEGORY_HPP

#include <string>
#include <cctype>

#include <fmt/format.h>
#include <tl/expected.hpp>

#include "util.hpp"
#include "error.hpp"

namespace cash_overflow::category {
enum class CategoryType {
  Assets,
  Liabilities,
  Incomes,
  Expenses
};

class IterableCategoryType
{
public:
  class Iterator
  {
  public:
    constexpr Iterator(int value) : m_value(value) {}
    constexpr CategoryType operator*() const
    {
      return static_cast<CategoryType>(m_value);
    }
    constexpr void operator++()
    {
      ++m_value;
    }
    constexpr auto operator<=>(Iterator const &) const = default;

  private:
    int m_value;
  };
};

constexpr IterableCategoryType::Iterator begin(IterableCategoryType)
{
  return IterableCategoryType::Iterator(static_cast<int>(CategoryType::Assets));
}

constexpr IterableCategoryType::Iterator end(IterableCategoryType)
{
  return IterableCategoryType::Iterator(static_cast<int>(CategoryType::Expenses) + 1);
}

inline std::string toString(CategoryType type)
{
  switch (type) {
  case CategoryType::Assets:
    return "Assets";
  case CategoryType::Liabilities:
    return "Liabilities";
  case CategoryType::Incomes:
    return "Incomes";
  case CategoryType::Expenses:
    return "Expenses";
  default:
    return "Uncategorized";
  }
}

inline tl::expected<CategoryType, cash_overflow::error::Error> fromString(std::string const &type)
{
  constexpr auto toLower = [](unsigned char c) -> char { return static_cast<char>(std::tolower(c)); };
  using cash_overflow::utils::map;
  using cash_overflow::utils::toString;

  std::string typeAsString = toString(map(type, toLower));
  if (typeAsString == "assets") {
    return CategoryType::Assets;
  } else if (typeAsString == "liabilities") {
    return CategoryType::Liabilities;
  } else if (typeAsString == "incomes") {
    return CategoryType::Incomes;
  } else if (typeAsString == "expenses") {
    return CategoryType::Expenses;
  } else {
    return tl::make_unexpected(fmt::format("Unknown Category Type: {}", typeAsString));
  }
}

inline std::vector<std::string> getAllValidCategoryNames()
{
  // return cash_overflow::utils::map(IterableCategoryType{}, toString); //seria fixe
  std::vector<std::string> allValidCategoryNames;
  for (auto x : IterableCategoryType{}) {
    allValidCategoryNames.push_back(toString(x));
  }
  return allValidCategoryNames;
}

struct Category
{
  Category(std::string n, CategoryType t) : name(std::move(n)), type{ t } {}
  std::string name;
  CategoryType type;
};
}// namespace cash_overflow::category


#endif// CASH_OVERFLOW_CATEGORY_HPP
