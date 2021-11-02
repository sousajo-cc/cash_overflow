# Proposal to report project metrics on a common format

## Problem
Currently there is an issue of ___row___ explosion when using the our RAII wrapper on a builder pattern.

Eg:
```
  irw::Table::Builder{}
    .with_id("Table")
    .with_number_of_columns(4)
    .with_headers({"Account/Category", "Remaining Budget", "Change", "Total"})
    .add_row({"Assets", "", {"$-778.32", Red}, "$29,754.72"})
    .add_row({"|- Cash", "", {"$-2.85", Red}, "$236.30"})
    .add_row({"|- Checking Account", "", {"$-634.99", Red}, "$7,327.01"})
    .add_row({"|- Euro Account", "", {"-120.00 EUR", Red}, "5,403.00 EUR"})
    .add_row({"|- Investment Account", "", "0 CNY", "20,400.00 CNY"})
    .add_row({"|- Savings Account", "", "$0.00", "$12,800.00"})
    .add_row({"Liabilities", "", {"$-200.00", Green}, "$11,400.00"})
    .add_row({"|- Car Loan", "", {"$-200.00", Green}, "$11,400.00"})
    .add_row({"Incomes", "-", "$0.00", "$18,853.50"})
    .add_row({"|- Other", "-", "$0.00", "$5,853.50"})
    .add_row({"|- Salary", "-", "$0.00", "$13,000.00"})
    .add_row({"Expenses", {"$226.67 of $460.00", Green}, {"$578.32", Red}, "$4,532.67"})
    .add_row({"|- Bills", "-", {"$30.00", Red}, "$3,092.00"})
    .add_row({"|- Clothing", {"$-40.48 of $100.00", Red}, {"$140.48", Red}, "$949.48"})
    .add_row({"|- Groceries", {"$74.15 of $160.00", Green}, {"$85.85", Red}, "$155.20"})
    .add_row({"|- Leisure", {"$193.00 of $200.00", Green}, {"$7.00", Red}, "$21.00"})
    .add_row({"|- Other", "-", {"$314.99", Red}, "$314.99"})
    .build();
```

If one could define a table via the means of a `json` file, one could have something like:
```
  irw::Table::Builder{}
    .from_file(<path to the json file>)
    .build();
```

In this document we will try to define such a format.

  

## Assumptions

We will take the table example from the `imgui_raii_wrapper` as the structure to be defined in the `json`.

One will have to define other formats as needed, as other object types appear in the project.

This will serve as a PoC.

## Proposal

### Used data types
| Data type                                 |            Description                    |        Example         |
| :---------------------------------------- | :---------------------------------------- | :--------------------- | 
| \<string\>                                |       Characters inside the quotes        |   "example of string"  |
| \<number\>                                |               Integers                    |         12             |
| \<color\>                                 |       Color - green, blue, yellow or red  |         blue           |

#### Header

```yaml
"table_info":
{
  "id": "<string>",
  "number_of_columns": "<number>",
}
```

#### Mandatory headers
```yaml
"headers": [
  {
    "name": "<string>",
  },
  {
    "name": "<string>",
  },
  (...)
]  
  (...)
]

```

The number of headers has to match the number of columns, unless we do want headerless columns.

#### Mandatory rows

```yaml
"rows": [
    {
        "title": "<string>",
        "content": [
          {
            "text": "<string>",
            "color": "<color>",
          },
          {
            "text": "<string>",
            "color": "<color>",
          },
          (...)
        ]    
    },
    (...)
]
```   

Again we ensure for each row we respect the header(column) structure.

This is just a first draft, and needs to be discussed and iterated, namely the items that should be included, and the schema itself (including the data types).
