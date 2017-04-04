#ifndef CG_RAW_MODEL_HPP
#define CG_RAW_MODEL_HPP

namespace CGCore
{
    // This class stores a model in memory
    class RawModel
    {
        private:
            int VaoID;
            int VertexCount;

            // prevent default construction
            RawModel() {};
        public:
            RawModel(int PVaoID, int PVertexCount) : VaoID(PVaoID), VertexCount(PVertexCount) {}

            inline int GetVaoID() { return VaoID; }
            inline int GetVertexCount() { return VertexCount; }
            
    };

} 

#endif