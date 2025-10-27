int main(int argc, char **argv)
{
    auto simulation = wrench::Simulation::createSimulation();

    simulation->init(&argc, argv);

    auto workflow = wrench::WfCommonsWorkflowParser::createWorkflowFromJSON(workflow_file, "100Gf", true);
   
    simulation->instantiatePlatform(platform_file);

    std::set<std::shared_ptr<wrench::StorageService>> storage_services;
    auto storage_service = simulation->add(wrench::SimpleStorageService::createSimpleStorageService(
        "WMSHost", {"/scratch/"}, {{wrench::SimpleStorageServiceProperty::BUFFER_SIZE, "50MB"}}, {}));

    std::vector<std::string> hostnames = {"VirtualizedClusterHost1", "VirtualizedClusterHost2", "VirtualizedClusterHost3"};

    std::cerr << "Instantiating an EnergyMeterService on WMSHost that monitors VirtualizedClusterHost1 every 10 seconds ..." << std::endl;
    auto energy_meter_service = simulation->add(new wrench::EnergyMeterService("WMSHost", hostnames, 10));

    simulation->getOutput().enableEnergyTimestamps(true);

    auto virtualized_cluster_service = simulation->add(new wrench::VirtualizedClusterComputeService(
        "VirtualizedClusterProviderHost", virtualized_cluster_hosts, "", {}, {}));
    auto wms = simulation->add(
        new wrench::Controller(workflow, virtualized_cluster_service, storage_service, "WMSHost"));

    auto file_registry_service = new wrench::FileRegistryService("WMSHost");
    simulation->add(file_registry_service);

    simulation->launch();
    
    auto energy_trace = simulation->getOutput().getTrace<wrench::SimulationTimestampEnergyConsumption>();
    
    simulation->getOutput().dumpHostEnergyConsumptionJSON("../results/{strategy}_{workflow}rnaseq_host_energy_consumption.json", true);

    return 0;
}
