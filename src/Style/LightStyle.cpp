// Copyright (c) 2015-2017, The Bytecoin developers
//
// This file is part of Bytecoin.
//
// Bytecoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Bytecoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Bytecoin.  If not, see <http://www.gnu.org/licenses/>.

#include "LightStyle.h"

namespace WalletGui {

LightStyle::LightStyle() : Style("light", "Light") {

}

QString LightStyle::statusBarBackgroundColor() const {
  return "#ffffff";
}

QString LightStyle::statusBarFontColor() const {
  return "#000000";
}

QString LightStyle::headerBackgroundColor() const {
  return "#ffffff";
}

QString LightStyle::headerBorderColor() const {
  return "#dddddd";
}

QString LightStyle::addressFontColor() const {
  return "#000000";
}

QString LightStyle::balanceFontColor() const {
  return "#000000";
}

QString LightStyle::toolButtonBackgroundColorNormal() const {
  return "#ffffff";
}

QString LightStyle::toolButtonBackgroundColorHover() const {
  return "#dae8f5";
}

QString LightStyle::toolButtonBackgroundColorPressed() const {
  return "#7bbeed";
}

QString LightStyle::toolButtonFontColorNormal() const {
  return "#000000";
}

QString LightStyle::toolButtonFontColorDisabled() const {
  return "#4d000000";
}

QString LightStyle::toolBarBorderColor() const {
  return "#dddddd";
}

QString LightStyle::getWalletSyncGifFile() const {
  return QString(":icons/light/wallet-sync");
}

QPixmap LightStyle::getLogoPixmap() const {
  return QPixmap(QString(":icons/light/logo"));
}

QPixmap LightStyle::getBalanceIcon() const {
  return QPixmap(QString(":icons/light/balance"));
}

QPixmap LightStyle::getConnectedIcon() const {
  return QPixmap(QString(":icons/light/connected"));
}

QPixmap LightStyle::getDisconnectedIcon() const {
  return QPixmap(QString(":icons/light/disconnected"));
}

QPixmap LightStyle::getEncryptedIcon() const {
  return QPixmap(QString(":icons/light/encrypted"));
}

QPixmap LightStyle::getNotEncryptedIcon() const {
  return QPixmap(QString(":icons/light/decrypted"));
}

QPixmap LightStyle::getSyncedIcon() const {
  return QPixmap(QString(":icons/light/synced"));
}

}
