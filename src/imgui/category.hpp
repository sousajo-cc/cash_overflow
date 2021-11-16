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
  // WARNING: the map implementation of the date branch will break this
  if (map(type, toLower) == "assets") {
    return CategoryType::Assets;
  } else if (map(type, toLower) == "liabilities") {
    return CategoryType::Liabilities;
  } else if (map(type, toLower) == "incomes") {
    return CategoryType::Incomes;
  } else if (map(type, toLower) == "expenses") {
    return CategoryType::Expenses;
  } else {
    return tl::make_unexpected(fmt::format("Unknown Category Type: {}", type));
  }
}

inline std::vector<std::string> getAllValidCategoryNames()
{
  return {};
}

struct Category
{
  Category(std::string n, CategoryType t) : name(std::move(n)), type{ t } {}
  std::string name;
  CategoryType type;
};
}// namespace cash_overflow::category


#endif// CASH_OVERFLOW_CATEGORY_HPP
