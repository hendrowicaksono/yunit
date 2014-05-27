/*
 * Copyright (C) 2013, 2014 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "fake_scope.h"
#include "fake_department.h"
#include "fake_resultsmodel.h"

Scope::Scope(QObject* parent) : Scope(QString(), QString(), false, parent)
{
}

Scope::Scope(QString const& id, QString const& name, bool visible, QObject* parent)
    : QObject(parent)
    , m_id(id)
    , m_name(name)
    , m_visible(visible)
    , m_searching(false)
    , m_isActive(false)
    , m_currentDeparment("root")
    , m_previewRendererName("preview-generic")
    , m_categories(new Categories(20, this))
{
}

QString Scope::id() const {
    return m_id;
}

QString Scope::name() const {
    return m_name;
}

QString Scope::searchQuery() const {
    return m_searchQuery;
}

QString Scope::iconHint() const {
    return m_iconHint;
}

QString Scope::description() const {
    return m_description;
}

QString Scope::searchHint() const {
    return QString("");
}

QString Scope::shortcut() const {
    return QString("");
}

bool Scope::connected() const {
    return true;
}

bool Scope::searchInProgress() const {
    return m_searching;
}

Categories* Scope::categories() const {
    return m_categories;
}

QString Scope::noResultsHint() const {
    return m_noResultsHint;
}

QString Scope::formFactor() const {
    return m_formFactor;
}

bool Scope::visible() const {
    return m_visible;
}

bool Scope::isActive() const {
    return m_isActive;
}

void Scope::setName(const QString &str) {
    if (str != m_name) {
        m_name = str;
        Q_EMIT nameChanged(m_name);
    }
}

void Scope::setSearchQuery(const QString &str) {
    if (str != m_searchQuery) {
        m_searchQuery = str;
        Q_EMIT searchQueryChanged();
    }
}

void Scope::setFormFactor(const QString &str) {
    if (str != m_formFactor) {
        m_formFactor = str;
        Q_EMIT formFactorChanged();
    }
}

void Scope::setActive(const bool active) {
    if (active != m_isActive) {
        m_isActive = active;
        Q_EMIT isActiveChanged(active);
    }
}

void Scope::setSearchInProgress(const bool inProg) {
    if (inProg != m_searching) {
        m_searching = inProg;
        Q_EMIT searchInProgressChanged();
    }
}

void Scope::setNoResultsHint(const QString& str) {
    if (str != m_noResultsHint) {
        m_noResultsHint = str;
        Q_EMIT noResultsHintChanged();
    }
}

void Scope::activate(QVariant const& result)
{
    Q_UNUSED(result);
}

PreviewStack* Scope::preview(QVariant const& result)
{
    Q_UNUSED(result);

    // This probably leaks, do we don't care
    // it's a  test after all
    return new PreviewStack;
}

void Scope::cancelActivation()
{
}

void Scope::closeScope(Scope* /*scope*/)
{
    qFatal("Scope::closeScope is not implemented");
}

QString Scope::currentDepartment() const
{
    return m_currentDeparment;
}

bool Scope::hasDepartments() const
{
    return true;
}

Department *Scope::getDepartment(const QString& id)
{
    if (id.isEmpty())
        return nullptr;

    QString parentId;
    QString parentLabel;
    if (id.startsWith("middle")) {
        parentId = "root";
        parentLabel = "root";
    } else if (id.startsWith("child")) {
        parentId = "middle";
        parentLabel = "middle";
    }
    return new Department(id, id, "all"+id, parentId, parentLabel, this);
}

void Scope::loadDepartment(const QString& id)
{
    m_currentDeparment = id;
    currentDepartmentChanged(m_currentDeparment);
}
