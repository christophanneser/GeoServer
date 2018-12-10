//
// Created by christoph on 10.12.18.
//

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "geoanalysis.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using geo::geoanalyser;
using geo::NeighborhoodCounts;
using geo::Point;
using geo::PointRequest;

// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public geoanalyser::Service {
    Status GetNeighborhoodsCount(ServerContext* context, const PointRequest* pointRequest, NeighborhoodCounts* response) override {
        // todo implement logic
        response->set_name("Maxvorstadt");
        response->set_count(1234);
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("192.168.52.71:50051");
    GreeterServiceImpl service;

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}