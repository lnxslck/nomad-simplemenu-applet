/***************************************************************************
 *   Copyright (C) 2014-2015 by Eike Hein <hein@kde.org>                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#ifndef FAVORITESMODEL_H
#define FAVORITESMODEL_H

#include "abstractmodel.h"

#include <QPointer>

#include <KService>

class FavoritesModel : public AbstractModel
{
    Q_OBJECT

    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QStringList favorites READ favorites WRITE setFavorites NOTIFY favoritesChanged)
    Q_PROPERTY(int maxFavorites READ maxFavorites WRITE setMaxFavorites NOTIFY maxFavoritesChanged)

    public:
        explicit FavoritesModel(QObject *parent = 0);
        ~FavoritesModel();

        QString description() const;

        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

        int rowCount(const QModelIndex &parent = QModelIndex()) const;

        Q_INVOKABLE bool trigger(int row, const QString &actionId, const QVariant &argument);

        bool enabled() const;
        void setEnabled(bool enable);

        QStringList favorites() const;
        void setFavorites(const QStringList &favorites);

        int maxFavorites() const;
        void setMaxFavorites(int max);

        Q_INVOKABLE bool isFavorite(const QString &id) const;
        Q_INVOKABLE void addFavorite(const QString &id);
        Q_INVOKABLE void removeFavorite(const QString &id);

        Q_INVOKABLE void moveRow(int from, int to);

        AbstractModel* favoritesModel();

    public Q_SLOTS:
        virtual void refresh();

    Q_SIGNALS:
        void enabledChanged() const;
        void favoritesChanged() const;
        void maxFavoritesChanged() const;

    private:
        AbstractEntry *favoriteFromId(const QString &id);

        bool m_enabled;

        QList<AbstractEntry *> m_entryList;
        QStringList m_favorites;
        int m_maxFavorites;
};

#endif
