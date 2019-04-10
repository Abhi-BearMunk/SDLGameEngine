# SDLGameEngine

This is a simple lightweight 2D game engine for PC built using SDL and Box2D.
Currently the engine is fully functional but not feature complete. I had started making this keeping Unity developers in mind so most of the terminology in the engine (GameObjects, Components, Scenes, Rigidbodies etc.) would be very familiar to those used to unity, but you should be right at home if you have experience with any EC framework.
The following functionalities are availible as of now in the master branch.

- A Entity Component framework 
- A layered sprite rendering system 
- Hierarchial Transform system
- An event system
- A basic prefab system
- Easy to use Keyboard and Mouse inputs
- A robust physics system with layering which respects the Transform hierarchy
- Rigidbodies, colliders, triggers (though only BoxColliders for now, Circles coming soon) and Raycasts
- Basic Text rendering
- Scene/ Level switching

Though not a part of the Master branch, the following can also be found in the Example Projects branch, which I will make a part of Master soon:
- A Behaviour Tree implementation
- A Steering Behaviour implementation

Please be aware that though I have done so wherever I could, this is still a personal project, which has not had rigorous bug testing, so use at your own risk.
Please email abhishekchandra2005@gmail.com if interested in collaborating.

