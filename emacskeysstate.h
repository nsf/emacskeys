#ifndef EMACSKEYSSTATE_H
#define EMACSKEYSSTATE_H

#include <QObject>

QT_FORWARD_DECLARE_CLASS(QPlainTextEdit)

namespace EmacsKeys {
namespace Internal {

enum EmacsKeysAction {
	EKA_3RD_PARTY,
	EKA_KILL_WORD,
	EKA_KILL_LINE,
	EKA_OTHER,
};

class EmacsKeysState : public QObject {
	Q_OBJECT

	bool m_ignore3rdParty;
	int m_mark;
	EmacsKeysAction m_lastAction;
	QPlainTextEdit *m_editorWidget;

public:
	EmacsKeysState(QPlainTextEdit *edit);
	~EmacsKeysState();
	void setLastAction(EmacsKeysAction action);
	void beginOwnAction() { m_ignore3rdParty = true; }
	void endOwnAction(EmacsKeysAction action) {
		m_ignore3rdParty = false;
		m_lastAction = action;
	}
	EmacsKeysAction lastAction() const { return m_lastAction; }

	int mark() const { return m_mark; }
	void setMark(int mark) { m_mark = mark; }

private slots:
	void cursorPositionChanged();
	void textChanged();
	void selectionChanged();
};

}} // namespace EmacsKeys::Internal

#endif // EMACSKEYSSTATE_H
