#ifndef CG_RENDERER_HPP
#define CG_RENDERER_HPP



namespace CGCore
{
    class RawModel;

    // Renderer class 
    class Renderer
    {
        private:

        public:
            void Prepare();
            void Render();
            void SetStates();
    };

} 

#endif
