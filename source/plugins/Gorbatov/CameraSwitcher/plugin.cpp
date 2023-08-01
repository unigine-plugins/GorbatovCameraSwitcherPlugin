#include <UniginePlugin.h>
#include <UnigineWorld.h>
#include <UnigineGame.h>
#include <UnigineConsole.h>

using namespace Unigine;

class CameraSwitcherPlugin: public Plugin
{
public:
	CameraSwitcherPlugin() {}
	virtual ~CameraSwitcherPlugin() override {}

	const char *get_name() override { return "CameraSwitcherPlugin"; }
	void *get_data() override { return nullptr; }

	int init() override
	{
		Log::message("Plugin CameraSwitcher is Initialized!\n");
		return 1;
	}
	
	int shutdown() override
	{
		return 1;
	}
	void update() override
	{
		if (Input::isKeyDown(Input::KEY_C) && !Console::isActive())
			next_camera();
	}

	void next_camera()
	{
		invalidate();
		
		if (players.size() == 0)
		{
			Log::error("CameraSwitcherPlugin: can not find any camera\n");
			return;
		}
		
		current_index++;
		if (current_index >= players.size())
			current_index = 0;
			
		auto p = players[current_index];
		Game::setPlayer(p);
		Log::message("current player is %s(%d)\n", p->getName(), p->getID());
	}

	void invalidate()
	{
		players.clear();
		Vector<NodePtr> nodes;
		World::getNodes(nodes);
		for (auto &it : nodes)
		{
			if (it && !it.isDeleted() && it->isPlayer() && it->isEnabled())
				players.append(checked_ptr_cast<Player>(it));
		}

		std::sort(players.front(), players.end(), [](PlayerPtr a, PlayerPtr b)
			{ return String(a->getName()) < String(b->getName()); });

		auto p = Game::getPlayer();
		if (p)
		{
			auto it = players.find(p);
			if (it != players.end())
				current_index = std::distance(players.front(), it);
		}
	}

	Vector<PlayerPtr> players;
	int current_index = -1;
};


//////////////////////////////////////////////////////////////////////////
// Plugin export
//////////////////////////////////////////////////////////////////////////

extern "C" UNIGINE_EXPORT void *CreatePlugin()
{
#ifdef USE_EVALUATION
	if (!Unigine::Engine::isEvaluation())
		return nullptr;
#endif
	return new CameraSwitcherPlugin();
}

extern "C" UNIGINE_EXPORT void ReleasePlugin(void *plugin)
{
	delete static_cast<CameraSwitcherPlugin *>(plugin);
}
