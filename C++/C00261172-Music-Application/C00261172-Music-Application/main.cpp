#include "Application.h"
#include "CharacterHelper.h"
int main() {
	CharacterHelper::fetchCharacterCodes();
	Application application = Application();
	application.run();
	return 0;
}