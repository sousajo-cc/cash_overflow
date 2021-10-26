#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QGroupBox>

#include "AccountsTab.hpp"

AccountsTab::AccountsTab(QWidget *parent)
  : QWidget(parent)
{

  QLabel *Assets = new QLabel(tr("Cash"));
  QLabel *Cash = new QLabel(tr("Cash"));
  Cash->setFrameStyle(QFrame::Panel | QFrame::Sunken);

  QLabel *Liabilities = new QLabel(tr("Liabilities"));
  QLabel *CarLoan = new QLabel(tr("CarLoan"));
  CarLoan->setFrameStyle(QFrame::Panel | QFrame::Sunken);


  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(Assets);
  mainLayout->addWidget(Cash);
  mainLayout->addWidget(Liabilities);
  mainLayout->addWidget(CarLoan);
  mainLayout->addStretch(1);
  setLayout(mainLayout);
}
