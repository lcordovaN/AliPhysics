
AliAnalysisTaskEbyeChargeFlucPbPb* AddTaskEbyeNetChargeFlucPbPb(
                                                                TString suffixName = "",
                                                                Bool_t MCthere = kFALSE,
                                                                Int_t zvtxcut = 10,
                                                                Int_t trackBit = 768,
                                                                Int_t MaxTPCclus = 100.,
                                                                Int_t TPCNclus =80.,
                                                                Double_t DCAxyCut =2.4,
                                                                Double_t DCAzCut =3.2
                                                                
                                                                )


{ // get the manager via the static access member. since it's static, you don't need
    // an instance of the class to call the function
    
    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr) {
        return 0x0;
    }
    
    if (!mgr->GetInputEventHandler()) {
        return 0x0;
    }
    
    TString fileName = AliAnalysisManager::GetCommonFileName();
    //    fileName += ":MyTask";
    
    // now we create an instance for task
    AliAnalysisTaskEbyeChargeFlucPbPb* task = new AliAnalysisTaskEbyeChargeFlucPbPb("");
    if(!task) return 0x0;
    
    //    if(MCthere){
    //        task->SetAnalysisType(MCthere);
    //    }
    
    // add your task to the manager
    mgr->AddTask(task);
    task->SetAnalysisType(MCthere);
    task->Setzvtxcut(zvtxcut);
    task->SettrackBit(trackBit);
    task->SetMaxTPCCluster(MaxTPCclus);
    task->SetNTPCCluster(TPCNclus);
    task->SetDCACut(DCAxyCut,DCAzCut);
    
    // Create containers for input/output
    TString finDirname      =   "_INT7";
    TString outBasicname    =   "EByE";
    TString profname1       =   "fTree";
    TString profname2       =   "fTreeMCrec";
    TString profname3       =   "fTreeMCgen";
    
    finDirname              +=   suffixName.Data();
    outBasicname            +=   finDirname.Data();
    profname1               +=   finDirname.Data();
    profname2               +=   finDirname.Data();
    profname3               +=   finDirname.Data();
    
    
    // your task needs input: here we connect the manager to your task
    mgr->ConnectInput(task,0,mgr->GetCommonInputContainer());
    
    // same for the output
    mgr->ConnectOutput(task,1,mgr->CreateContainer(outBasicname, TList::Class(), AliAnalysisManager::kOutputContainer, fileName.Data()));
    mgr->ConnectOutput(task,2,mgr->CreateContainer(profname1, TTree::Class(), AliAnalysisManager::kOutputContainer, fileName.Data()));
    mgr->ConnectOutput(task,3,mgr->CreateContainer(profname2, TTree::Class(), AliAnalysisManager::kOutputContainer, fileName.Data()));
    mgr->ConnectOutput(task,4,mgr->CreateContainer(profname3, TTree::Class(), AliAnalysisManager::kOutputContainer, fileName.Data()));
    
    return task;
    
}
