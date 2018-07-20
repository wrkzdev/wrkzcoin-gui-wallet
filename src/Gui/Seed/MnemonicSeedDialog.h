// Copyright (c) 2017 The Karbowanec developers
// Copyright (C) 2018 The WRKZCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <QDialog>

namespace Ui {
class MnemonicSeedDialog;
}

namespace WalletGui {

class MnemonicSeedDialog : public QDialog {
    Q_OBJECT

public:
    MnemonicSeedDialog(const QByteArray& _key, QWidget * _parent);
    ~MnemonicSeedDialog();

private:
    QScopedPointer<Ui::MnemonicSeedDialog> m_ui;

    void initLanguages();
    QString getLanguageName();
	QByteArray _Currentkey;
    Q_SLOT void languageChanged();
};

}
