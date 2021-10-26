#ifndef CASH_OVERFLOW_TABDIALOG_HPP
#define CASH_OVERFLOW_TABDIALOG_HPP

#include <QWidget>
#include <QTabWidget>
#include <QDialog>
#include <QDialogButtonBox>

class TabDialog : public QDialog
{
  Q_OBJECT // Very Important, this is all the magic that is needed
public:
  explicit TabDialog(QWidget *parent = nullptr);

  // No need for a destructor (~HelloQt) here, the parent system makes sure that all the elements that
  // are parented to this is cleaned up

private:
  QTabWidget *tabWidget;
  QDialogButtonBox *buttonBox;
  void writeToDebug();
};

#endif
