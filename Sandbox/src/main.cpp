#include "Bipolar.h"
#include "Test3D.h"

class Game : public Application
{
public:
	Game()
		: Application("Bipolar", 1366, 768)
	{
		addLayer(new Test3D());
	}
};

int main()
{
	Game game;
	game.start();
	return 0;
}
