#ifndef CG_RENDERER_HPP
#define CG_RENDERER_HPP



namespace CGCore
{

    class TexturedModel;
    // Renderer class 
    class Renderer
    {
        private:

        public:
            void Prepare();
            void Render(CGCore::TexturedModel* Model);
    };

} 

#endif