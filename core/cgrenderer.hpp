#ifndef CG_RENDERER_HPP
#define CG_RENDERER_HPP

class RawModel;
namespace CGCore
{

    
    // Renderer class 
    class Renderer
    {
        private:

        public:
            void Prepare();
            void Render(RawModel Model);
    };

} 

#endif