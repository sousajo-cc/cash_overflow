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
  Expenses,
  First = Assets,// First and Last allow to iterate
  Last = Expenses
};

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
  using cash_overflow::utils::toLowerCase;

  std::string typeAsString = toLowerCase(type);
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

// maybe return std::array since size is know at compile time
inline std::vector<std::string> getAllValidCategoryNames()
{
  // return cash_overflow::utils::map(IterableEnum{}, toString); //seria fixe
  using cash_overflow::utils::EnumIterator;
  using cash_overflow::utils::size;
  std::vector<std::string> allValidCategoryNames;
  allValidCategoryNames.reserve(size<CategoryType>());
  for (auto x : EnumIterator<CategoryType>{}) {
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
