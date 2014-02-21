#include "emacskeysstate.h"

#include <QTextCursor>
#include <QPlainTextEdit>

using namespace EmacsKeys::Internal;

//---------------------------------------------------------------------------
// EmacsKeysState
//---------------------------------------------------------------------------

EmacsKeysState::EmacsKeysState(QPlainTextEdit *edit):
	m_ignore3rdParty(false),
	m_mark(-1),
	m_lastAction(EKA_3RD_PARTY),
	m_editorWidget(edit)
{
	connect(edit, SIGNAL(cursorPositionChanged()),
		this, SLOT(cursorPositionChanged()));
	connect(edit, SIGNAL(textChanged()),
		this, SLOT(textChanged()));
	connect(edit, SIGNAL(selectionChanged()),
		this, SLOT(selectionChanged()));
}

EmacsKeysState::~EmacsKeysState() {}

void EmacsKeysState::setLastAction(EmacsKeysAction action)
{
	if (m_mark != -1) {
		// this code can be triggered only by 3rd party actions
		beginOwnAction();
		QTextCursor cursor = m_editorWidget->textCursor();
		cursor.clearSelection();
		m_editorWidget->setTextCursor(cursor);
		m_mark = -1;
		endOwnAction(action);
	} else {
		m_lastAction = action;
	}
}

void EmacsKeysState::cursorPositionChanged() {
	if (!m_ignore3rdParty)
		setLastAction(EKA_3RD_PARTY);
}

void EmacsKeysState::textChanged() {
	if (!m_ignore3rdParty)
		setLastAction(EKA_3RD_PARTY);
}

void EmacsKeysState::selectionChanged()
{
	if (!m_ignore3rdParty)
		setLastAction(EKA_3RD_PARTY);
}

