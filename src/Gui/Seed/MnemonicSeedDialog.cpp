// Copyright (c) 2017 The Karbowanec developers
// Copyright (C) 2018 The WRKZCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "MnemonicSeedDialog.h"
#include "ui_mnemonicseeddialog.h"
#include "CryptoNoteCore/Currency.h"

#include "IWalletAdapter.h"

#include "Mnemonics/electrum-words.h"
#include "Settings/Settings.h"

namespace WalletGui {

AccountKeys convertByteArrayToAccountKeys(const QByteArray& _array) {
  AccountKeys accountKeys;
  QDataStream trackingKeysDataStream(_array);
  trackingKeysDataStream.readRawData(reinterpret_cast<char*>(&accountKeys.spendKeys.publicKey), sizeof(Crypto::PublicKey));
  trackingKeysDataStream.readRawData(reinterpret_cast<char*>(&accountKeys.viewKeys.publicKey), sizeof(Crypto::PublicKey));
  trackingKeysDataStream.readRawData(reinterpret_cast<char*>(&accountKeys.spendKeys.secretKey), sizeof(Crypto::SecretKey));
  trackingKeysDataStream.readRawData(reinterpret_cast<char*>(&accountKeys.viewKeys.secretKey), sizeof(Crypto::SecretKey));
  return accountKeys;
}

MnemonicSeedDialog::MnemonicSeedDialog(const QByteArray& _key, QWidget* _parent) : QDialog(_parent), m_ui(new Ui::MnemonicSeedDialog) {
  m_ui->setupUi(this);	
  initLanguages();
  m_ui->m_languageCombo->setCurrentIndex(m_ui->m_languageCombo->findData(getLanguageName(), Qt::DisplayRole));

	// TODO
	_Currentkey = _key;
	AccountKeys accountKeys = convertByteArrayToAccountKeys(_key);
	std::string mnemonicSeed;
	std::string seed_language = getLanguageName().toUtf8().constData();
	//seed_language = "English";
    crypto::ElectrumWords::bytes_to_words(accountKeys.spendKeys.secretKey, mnemonicSeed, seed_language);
	m_ui->m_mnemonicSeedEdit->setText(QString::fromStdString(mnemonicSeed));
	
}

MnemonicSeedDialog::~MnemonicSeedDialog() {
}

void MnemonicSeedDialog::initLanguages() {
  std::vector<std::string> languages;
  crypto::ElectrumWords::get_language_list(languages);
  for (size_t i = 0; i < languages.size(); ++i)
  {
    m_ui->m_languageCombo->addItem(QString::fromStdString(languages[i]));
  }
}

void MnemonicSeedDialog::languageChanged() {
	// TODO
	AccountKeys accountKeys = convertByteArrayToAccountKeys(_Currentkey);
	std::string mnemonicSeed;
	std::string seed_language = m_ui->m_languageCombo->currentText().toUtf8().constData();
	//seed_language = "English";
    crypto::ElectrumWords::bytes_to_words(accountKeys.spendKeys.secretKey, mnemonicSeed, seed_language);
	m_ui->m_mnemonicSeedEdit->setText(QString::fromStdString(mnemonicSeed));
}

QString MnemonicSeedDialog::getLanguageName() {
  QString lng = Settings::instance().getLanguage();
  QString lang;
  if (lng == "English") {
      lang = "English";
    } else if(lng == "Nederlands") {
      lang = "Dutch";
    } else if(lng == "Français") {
      lang = "French";
    } else if(lng == "Español") {
      lang = "Spanish";
    } else if(lng == "Português") {
      lang = "Portuguese";
    } else if(lng == "日本語") {
      lang = "Japanese";
    } else if(lng == "Italiano") {
      lang = "Italian";
    } else if(lng == "Deutsch") {
      lang = "German";
    } else if(lng == "русский язык") {
      lang = "Russian";
    } else if(lng == "简体中文 (中国)") {
      lang = "Chinese_Simplified";
    } else if(lng == "Esperanto") {
      lang = "Esperanto";
    } else if(lng == "Lojban") {
      lang = "Lojban";
    } else {
      lang = "English";
    }
  return lang;
}

}
