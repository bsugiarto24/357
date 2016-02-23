##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Test
ConfigurationName      :=Debug
WorkspacePath          := "C:\Users\Bryan\Desktop\CPE 357\Test\BitOps"
ProjectPath            := "C:\Users\Bryan\Desktop\CPE 357\Test\BitOps\Test"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Bryan
Date                   :=02/06/15
CodeLitePath           :="C:\Program Files (x86)\CodeLite"
LinkerName             :=C:/MinGW-4.8.1/bin/g++.exe 
SharedObjectLinkerName :=C:/MinGW-4.8.1/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Test.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/MinGW-4.8.1/bin/windres.exe 
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/MinGW-4.8.1/bin/ar.exe rcu
CXX      := C:/MinGW-4.8.1/bin/g++.exe 
CC       := C:/MinGW-4.8.1/bin/gcc.exe 
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/MinGW-4.8.1/bin/as.exe 


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files (x86)\CodeLite
UNIT_TEST_PP_SRC_DIR:=C:\UnitTest++-1.3
Objects0=$(IntermediateDirectory)/SmartAlloc.c$(ObjectSuffix) $(IntermediateDirectory)/LZWExp.c$(ObjectSuffix) $(IntermediateDirectory)/TestExp.c$(ObjectSuffix) $(IntermediateDirectory)/CodeSet.c$(ObjectSuffix) $(IntermediateDirectory)/BitUnpacker.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/SmartAlloc.c$(ObjectSuffix): SmartAlloc.c $(IntermediateDirectory)/SmartAlloc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Bryan/Desktop/CPE 357/Test/BitOps/Test/SmartAlloc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SmartAlloc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SmartAlloc.c$(DependSuffix): SmartAlloc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SmartAlloc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/SmartAlloc.c$(DependSuffix) -MM "SmartAlloc.c"

$(IntermediateDirectory)/SmartAlloc.c$(PreprocessSuffix): SmartAlloc.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SmartAlloc.c$(PreprocessSuffix) "SmartAlloc.c"

$(IntermediateDirectory)/LZWExp.c$(ObjectSuffix): LZWExp.c $(IntermediateDirectory)/LZWExp.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Bryan/Desktop/CPE 357/Test/BitOps/Test/LZWExp.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/LZWExp.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/LZWExp.c$(DependSuffix): LZWExp.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/LZWExp.c$(ObjectSuffix) -MF$(IntermediateDirectory)/LZWExp.c$(DependSuffix) -MM "LZWExp.c"

$(IntermediateDirectory)/LZWExp.c$(PreprocessSuffix): LZWExp.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/LZWExp.c$(PreprocessSuffix) "LZWExp.c"

$(IntermediateDirectory)/TestExp.c$(ObjectSuffix): TestExp.c $(IntermediateDirectory)/TestExp.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Bryan/Desktop/CPE 357/Test/BitOps/Test/TestExp.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestExp.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestExp.c$(DependSuffix): TestExp.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestExp.c$(ObjectSuffix) -MF$(IntermediateDirectory)/TestExp.c$(DependSuffix) -MM "TestExp.c"

$(IntermediateDirectory)/TestExp.c$(PreprocessSuffix): TestExp.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestExp.c$(PreprocessSuffix) "TestExp.c"

$(IntermediateDirectory)/CodeSet.c$(ObjectSuffix): CodeSet.c $(IntermediateDirectory)/CodeSet.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Bryan/Desktop/CPE 357/Test/BitOps/Test/CodeSet.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CodeSet.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CodeSet.c$(DependSuffix): CodeSet.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CodeSet.c$(ObjectSuffix) -MF$(IntermediateDirectory)/CodeSet.c$(DependSuffix) -MM "CodeSet.c"

$(IntermediateDirectory)/CodeSet.c$(PreprocessSuffix): CodeSet.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CodeSet.c$(PreprocessSuffix) "CodeSet.c"

$(IntermediateDirectory)/BitUnpacker.c$(ObjectSuffix): BitUnpacker.c $(IntermediateDirectory)/BitUnpacker.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Bryan/Desktop/CPE 357/Test/BitOps/Test/BitUnpacker.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BitUnpacker.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/BitUnpacker.c$(DependSuffix): BitUnpacker.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/BitUnpacker.c$(ObjectSuffix) -MF$(IntermediateDirectory)/BitUnpacker.c$(DependSuffix) -MM "BitUnpacker.c"

$(IntermediateDirectory)/BitUnpacker.c$(PreprocessSuffix): BitUnpacker.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/BitUnpacker.c$(PreprocessSuffix) "BitUnpacker.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) ./Debug/*$(ObjectSuffix)
	$(RM) ./Debug/*$(DependSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile).exe
	$(RM) "../.build-debug/Test"


