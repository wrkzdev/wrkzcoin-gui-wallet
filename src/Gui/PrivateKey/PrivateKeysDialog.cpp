// Copyright (c) 2016 The Karbowanec developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "PrivateKeysDialog.h"
#include "ui_privatekeysdialog.h"
#include <QClipboard>
#include <Common/Base58.h>
// #include "CurrencyAdapter.h"
#include "CryptoNoteCore/Currency.h"
#include "IWalletAdapter.h"
#include "Settings/Settings.h"
//#include "WalletAdapter.h"
#include <Common/FormatTools.h>
#include <Common/StringTools.h>
#include <CryptoNoteCore/Account.h>

namespace WalletGui {
	
AccountKeys convertByteArrayToAccountKeys2(const QByteArray& _array) {
  AccountKeys accountKeys;
  QDataStream trackingKeysDataStream(_array);
  trackingKeysDataStream.readRawData(reinterpret_cast<char*>(&accountKeys.spendKeys.publicKey), sizeof(Crypto::PublicKey));
  trackingKeysDataStream.readRawData(reinterpret_cast<char*>(&accountKeys.viewKeys.publicKey), sizeof(Crypto::PublicKey));
  trackingKeysDataStream.readRawData(reinterpret_cast<char*>(&accountKeys.spendKeys.secretKey), sizeof(Crypto::SecretKey));
  trackingKeysDataStream.readRawData(reinterpret_cast<char*>(&accountKeys.viewKeys.secretKey), sizeof(Crypto::SecretKey));
  return accountKeys;
}

PrivateKeysDialog::PrivateKeysDialog(const QByteArray& _key, QWidget* _parent) : QDialog(_parent), m_ui(new Ui::PrivateKeysDialog) {
  m_ui->setupUi(this);	

  _Currentkey = _key;
  AccountKeys accountKeys = convertByteArrayToAccountKeys2(_key);
  const Crypto::SecretKey privateViewKey = accountKeys.viewKeys.secretKey;
  Crypto::SecretKey privateSpendKey = accountKeys.spendKeys.secretKey;
  
  Crypto::SecretKey derivedPrivateViewKey;
  CryptoNote::AccountBase::generateViewFromSpend(privateSpendKey,
                                                   derivedPrivateViewKey);
  std::string _ViewKey;
  std::string _Spendey;
  _Spendey = Common::podToHex(privateSpendKey);
  _ViewKey = Common::podToHex(privateViewKey);

  m_ui->m_privateKeyEdit->setText("Private Spendkey: "+QString::fromStdString(_Spendey)+"\n"
						+"Private Viewkey: "+QString::fromStdString(_ViewKey));	
}

PrivateKeysDialog::~PrivateKeysDialog() {
}

void PrivateKeysDialog::walletClosed() {
  m_ui->m_privateKeyEdit->clear();
}

void PrivateKeysDialog::copyKey() {
  QApplication::clipboard()->setText(m_ui->m_privateKeyEdit->toPlainText());
}

}
