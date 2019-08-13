/*
 * Copyright 2015-2019  Thomas Baumgart <tbaumgart@kde.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "newtransactionform.h"

// ----------------------------------------------------------------------------
// QT Includes

#include <QDate>

// ----------------------------------------------------------------------------
// KDE Includes

// ----------------------------------------------------------------------------
// Project Includes

#include "ui_newtransactionform.h"
#include "ledgermodel.h"
#include "modelenums.h"

using namespace eLedgerModel;

class NewTransactionForm::Private
{
public:
  Private()
  : ui(new Ui_NewTransactionForm)
  {
  }

  ~Private()
  {
    delete ui;
  }

  Ui_NewTransactionForm*      ui;
  QString                     transactionSplitId;
};


NewTransactionForm::NewTransactionForm(QWidget* parent)
  : QFrame(parent)
  , d(new Private)
{
  d->ui->setupUi(this);
}

NewTransactionForm::~NewTransactionForm()
{
  delete d;
}

void NewTransactionForm::showTransaction(const QString& transactionSplitId)
{
  d->transactionSplitId = transactionSplitId;

  /// @todo port to new model code
#if 0
  const QAbstractItemModel* model = Models::instance()->ledgerModel();
  const QModelIndexList indexes = model->match(model->index(0, 0, QModelIndex()),
                                              (int)Role::TransactionSplitId,
                                              QVariant(transactionSplitId),
                                              1,
                                              Qt::MatchFlags(Qt::MatchExactly | Qt::MatchCaseSensitive));
  if(indexes.count() == 1) {
    const QModelIndex index = indexes.first();
    d->ui->dateEdit->setText(QLocale().toString(model->data(index, (int)Role::PostDate).toDate(),
                                                           QLocale::ShortFormat));
    d->ui->payeeEdit->setText(model->data(index, (int)Role::PayeeName).toString());
    d->ui->memoEdit->clear();
    d->ui->memoEdit->insertPlainText(model->data(index, (int)Role::Memo).toString());
    d->ui->memoEdit->moveCursor(QTextCursor::Start);
    d->ui->memoEdit->ensureCursorVisible();
    d->ui->accountEdit->setText(model->data(index, (int)Role::CounterAccount).toString());
    d->ui->statusEdit->setText(model->data(index, (int)Role::ReconciliationLong).toString());
    QString amount = QString("%1 %2").arg(model->data(index, (int)Role::ShareAmount).toString())
    .arg(model->data(index, (int)Role::ShareAmountSuffix).toString());
    d->ui->amountEdit->setText(amount);
    d->ui->numberEdit->setText(model->data(index, (int)Role::Number).toString());
  }
#endif
}

void NewTransactionForm::modelDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
  const QAbstractItemModel * const model = topLeft.model();
  const int startRow = topLeft.row();
  const int lastRow = bottomRight.row();
  for(int row = startRow; row <= lastRow; ++row) {
    QModelIndex index = model->index(row, 0);
    if(model->data(index, (int)eLedgerModel::Role::TransactionSplitId).toString() == d->transactionSplitId) {
      showTransaction(d->transactionSplitId);
      break;
    }
  }
}
