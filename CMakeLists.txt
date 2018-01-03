# cmake_minimum_required(VERSION <specify CMake version here>)
project(Blogel)

set(CMAKE_CXX_STANDARD 11)

add_executable(Blogel
        basic/MessageBuffer.h
        basic/pregel-dev.h
        basic/Vertex.h
        basic/Worker.h
        blogel/BAggregator.h
        blogel/BAssign.h
        blogel/BGlobal.h
        blogel/Block.h
        blogel/BMessageBuffer.h
        blogel/BType.h
        blogel/BVecs.h
        blogel/BVertex.h
        blogel/BWorker.h
        blogel/Heap.h
        blogel/STRPart.h
        blogel/STRPartR2.h
        blogel/VMessageBuffer.h
        blogel/Voronoi.h
        utils/Aggregator.h
        utils/Combiner.h
        utils/communication.h
        utils/global.h
        utils/log.h
        utils/serialization.h
        utils/TeraSort.h
        utils/time.h
        utils/type.h
        utils/vecs.h
        utils/ydhdfs.h
        run.cpp
        blogel_app_sssp.h
        blogel_sssp_vorPart.h
        run_vorPart.cpp
        put.cpp)
