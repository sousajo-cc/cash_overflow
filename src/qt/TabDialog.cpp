#include "TabDialog.hpp"
#include <QHBoxLayout>
#include <QtWidgets>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

#include "AccountsTab.hpp"

TabDialog::TabDialog(QWidget *parent) : QDialog(parent)
{
  tabWidget = new QTabWidget;
  tabWidget->addTab(new AccountsTab(), tr("General"));
  tabWidget->addTab(new AccountsTab(), tr("This IS BORIIIIIING"));
  tabWidget->addTab(new QWidget(), tr("SuareZ"));


  buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                   | QDialogButtonBox::Cancel);

  connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(tabWidget);
  mainLayout->addWidget(buttonBox);
  setLayout(mainLayout);
}

void TabDialog::writeToDebug(void)
{
  qDebug() << tr("I don't know what I was supposed to debug here...");
}
