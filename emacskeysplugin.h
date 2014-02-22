#ifndef EMACSKEYS_H
#define EMACSKEYS_H

#include "emacskeys_global.h"

#include <extensionsystem/iplugin.h>

#include <QTextCursor>

// forward declarations
QT_FORWARD_DECLARE_CLASS(QAction)
QT_FORWARD_DECLARE_CLASS(QPlainTextEdit)

namespace Core {
class Id;
class IEditor;
}

namespace EmacsKeys {
namespace Internal {

class EmacsKeysState;

class EmacsKeysPlugin : public ExtensionSystem::IPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "EmacsKeys.json")

public:
	EmacsKeysPlugin();
	~EmacsKeysPlugin();

	bool initialize(const QStringList &arguments, QString *errorString);
	void extensionsInitialized();
	ShutdownFlag aboutToShutdown();

private slots:
	void editorAboutToClose(Core::IEditor *editor);
	void currentEditorChanged(Core::IEditor *editor);

	void deleteCharacter();       // C-d
	void killWord();              // M-d
	void killLine();              // C-k

	void gotoFileStart();         // M-<
	void gotoFileEnd();           // M->
	void gotoLineStart();         // C-a
	void gotoLineEnd();           // C-e
	void gotoNextLine();          // C-n
	void gotoPreviousLine();      // C-p
	void gotoNextCharacter();     // C-f
	void gotoPreviousCharacter(); // C-b
	void gotoNextWord();          // M-f
	void gotoPreviousWord();      // M-b

	void mark();                  // C-SPC
	void exchangeCursorAndMark(); // C-x C-x
	void copy();                  // M-w
	void cut();                   // C-w
	void yank();                  // C-y

	void scrollHalfDown();        // C-v
	void scrollHalfUp();          // M-v

private:
	QAction *registerAction(const Core::Id &id, const char *slot,
		const QString &title);
	void genericGoto(QTextCursor::MoveOperation op);
	void genericVScroll(int direction);

	QHash<QPlainTextEdit*, EmacsKeysState*> m_stateMap;
	QPlainTextEdit *m_currentEditorWidget;
	EmacsKeysState *m_currentState;
};

} // namespace Internal
} // namespace EmacsKeys

#endif // EMACSKEYS_H

