#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <set>
#include <fstream>
#include <iomanip>
#include <stdio.h>

using namespace std;






//000000 rs rt rd 00000 funct

map<string,string> create_R_Type_1_funct_map(){
    map<string,string> m;
    m["add"]="100000";
    m["addu"]="100001";
    m["and"]="100100";
    m["nor"]="100111";
    m["or"]="100101";
    m["sllv"]="000100";
    m["srav"]="000111";
    m["srlv"]="000110";
    m["sub"]="100010";
    m["subu"]="100011";
    m["xor"]="100110";
    m["slt"]="101010";
    m["sltu"]="101011";
    return m;

}

//000000 rs rt rd shamt funct

map<string,string> create_R_Type_2_funct_map(){
    map<string,string> m;
    m["sll"]="000000";
    m["sra"]="000011";
    m["srl"]="000010";
    return m;
}

//000000 rs rt 0000000000 funct

//map R3 funct to binary
map<string,string> create_R_Type_3_funct_map(){
    map<string,string> m;
    m["div"]="011010";
    m["divu"]="011011";
    m["mult"]="011000";
    m["multu"]="011001";
    m["teq"]="110100";
    m["tne"]="110110";
    m["tge"]="110000";
    m["tgeu"]="110001";
    m["tlt"]="110010";
    m["tltu"]="110011";
    return m;
}

//op rs rt imm

//map I1 op to binary
map<string,string> create_I_Type_1_op_map(){
    map<string,string> m;
    m["addi"]="001000";
    m["addiu"]="001001";
    m["andi"]="001100";
    m["xori"]="001110";
    m["ori"]="001101";
    m["slti"]="001010";
    m["sltiu"]="001011";
    return m;

}

//000001 rs ??? imm

//map I2 ????? to binary
map<string,string> create_I_Type_2_nnnnn_map(){
    map<string,string> m;
    m["teqi"]="01100";
    m["tnei"]="01110";
    m["tgei"]="01000";
    m["tgeiu"]="01001";
    m["tlti"]="01010";
    m["tltiu"]="01011";
    return m;
}

//op 00000 rt imm

map<string,string> create_I_Type_3_op_map(){
    map<string,string> m;
    m["lui"]="001111";

    return m;
}


//op rs rt offset(label)

map<string,string> create_Branch_Type_1_op_map(){
    map<string,string> m;
    m["beq"]="000100";
    m["bne"]="000101";

    return m;
}
//map B1 op to binary

//op rs ??? offset(label)


map<string,string> create_Branch_Type_2_op_map(){
    map<string,string> m;
    m["bgez"]="000001";
    m["bgezal"]="000001";
    m["bgtz"]="000111";
    m["blez"]="000110";
    m["bltzal"]="000001";
    m["bltz"]="000001";
    return m;
}

map<string,string> create_Branch_Type_2_nnnnn_map(){
    map<string,string> m;
    m["bgez"]="00001";
    m["bgezal"]="10001";
    m["bgtz"]="00000";
    m["blez"]="00000";
    m["bltzal"]="10000";
    m["bltz"]="00000";
    return m;
}

//op target


map<string,string> create_Jump_Type_1_op_map(){
    map<string,string> m;
    m["j"]="000010";
    m["jal"]="000011";

    return m;
}

//000000 rs 00000 rd 00000 001001

//000000 rs 000000000000000 1000

//op rs rt offset(address)


map<string,string> create_Load_Type_1_op_map(){
    map<string,string> m;
    m["lb"]="100000";
    m["lbu"]="100100";
    m["lh"]="100001";
    m["lhu"]="100101";
    m["lw"]="100011";
    m["lwl"]="100010";
    m["lwr"]="100110";
    m["ll"]="110000";
    m["sb"]="101000";
    m["sh"]="101001";
    m["sw"]="101011";
    m["swl"]="101010";
    m["swr"]="101110";
    m["sc"]="111000";
    return m;
}

//000000 0000000000 rd ???


map<string,string> create_MF_Type_1_nnnnnn_map(){
    map<string,string> m;
    m["mfhi"]="010000";
    m["mflo"]="010010";

    return m;
}

//000000 rs 000000000000000 ??????

map<string,string> create_MF_Type_2_nnnnnn_map(){
    map<string,string> m;
    m["mthi"]="010001";
    m["mtlo"]="010011";

    return m;
}
map<string,string> create_register_number_map(){
    map<string,string> registermap;
    registermap["zero"]="00000";
     registermap["$at"]="00001";
        registermap["$v0"]="00010";
        registermap["$v1"]="00011";
        registermap["$a0"]="00100";
        registermap["$a1"]="00101";
        registermap["$a2"]="00110";
        registermap["$a3"]="00111";
        registermap["$t0"]="01000";
        registermap["$t1"]="01001";
        registermap["$t2"]="01010";
        registermap["$t3"]="01011";
        registermap["$t4"]="01100";
        registermap["$t5"]="01101";
        registermap["$t6"]="01110";
        registermap["$t7"]="01111";
        registermap["$s0"]="10000";
        registermap["$s1"]="10001";
        registermap["$s2"]="10010";
        registermap["$s3"]="10011";
        registermap["$s4"]="10100";
        registermap["$s5"]="10101";
        registermap["$s6"]="10110";
        registermap["$s7"]="10111";
        registermap["$t8"]="11000";
        registermap["$t9"]="11001";
        registermap["$k0"]="11010";
        registermap["$k1"]="11011";
        registermap["$gp"]="11100";
        registermap["$sp"]="11101";
        registermap["$s8"]="11110";
        registermap["$fp"]="11110";
        registermap["$ra"]="11111";
        return registermap;
}

string promptUserForFile(ifstream &stream){
        while (true)
        {cout<<"Input file: ";
        string filename;
        getline(cin,filename);
        stream.open(filename.c_str());
        if (!stream.fail()){
            return filename;
        }
        stream.clear();
        cout<<"Unable to open that file. Try again"<<endl;

        }
    }

int findBinary(int decimal){
    int binary;
    if(decimal==0){
        binary=0;
    }
    else{
        binary=decimal%2+10*(findBinary(decimal/2));
    }
    return binary;
}


string decToBin(int decimal){
    int binary=findBinary(decimal);
    stringstream ss;
    string stringBinary;
    ss<<binary;
    ss>>stringBinary;
    return stringBinary;

}
void removeCommaAndCommentsAndLabelAndBracketAndWS(string &a){
    /*string a="main: add 100($t1), $t2, $t3#comment#";*/

    for(unsigned j=0;j<a.size();j++){
        if ((a[j]==',')||(a[j]=='(')||(a[j]==')')||a[j]==' '){
            a.erase(a.begin()+j);
        }
    }
    string::size_type l=a.find('#');
    if (l!=string::npos){
        a.erase(l,a.length()-l);
    }
    string::size_type z=a.find(':');//删掉标签
    if(z!=string::npos){
        a.erase(0,z+1);
    }
}
void createlinevector(string&str,vector<string>&Elementvector){
    string::size_type dollarpos, start;
    start=0;
    dollarpos=str.find("$");
    string op=str.substr(0,dollarpos);
    //000000 rs rt rd 00000 funct
set<string> R_Type_1_op;
R_Type_1_op.insert("add");
R_Type_1_op.insert("addu");
R_Type_1_op.insert("and");
R_Type_1_op.insert("nor");
R_Type_1_op.insert("or");
R_Type_1_op.insert("sllv");
R_Type_1_op.insert("srav");
R_Type_1_op.insert("srlv");
R_Type_1_op.insert("sub");
R_Type_1_op.insert("subv");
R_Type_1_op.insert("xor");
R_Type_1_op.insert("slt");
R_Type_1_op.insert("sltu");

                   /*, "addu", "and", "nor", "or", "sllv", "srav",
                    * "srlv", "sub", "subv", "xor", "slt", "sltu"});
    //map R1 funct to binary*/

map<string,string> R_Type_1_funct_map=create_R_Type_1_funct_map();

    //000000 rs rt rd shamt funct
set<string> R_Type_2_op;
R_Type_2_op.insert("sll");
R_Type_2_op.insert("sra");
R_Type_2_op.insert("srl");
        //"sll", "sra", "srl"

    //map R2 funct to binary

map<string,string> R_Type_2_funct_map=create_R_Type_2_funct_map();

    //000000 rs rt 0000000000 funct
set<string> R_Type_3_op;
R_Type_3_op.insert("div");
R_Type_3_op.insert("divu");
R_Type_3_op.insert("mult");
R_Type_3_op.insert("multu");
R_Type_3_op.insert("teq");
R_Type_3_op.insert("tne");
R_Type_3_op.insert("tge");
R_Type_3_op.insert("tgeu");
R_Type_3_op.insert("tlt");
R_Type_3_op.insert("tltu");

        /*"div", "divu", "mult", "multu", "teq", "tne", "tge", "tgeu",
    "tlt", "tltu"*/

    //map R3 funct to binary

map<string,string> R_Type_3_funct_map=create_R_Type_3_funct_map();
    //op rs rt imm
set<string> I_Type_1_op;
I_Type_1_op.insert("addi");
I_Type_1_op.insert("addiu");
I_Type_1_op.insert("andi");
I_Type_1_op.insert("xori");
I_Type_1_op.insert("ori");
I_Type_1_op.insert("slti");
I_Type_1_op.insert("sltiu");

        //"addi", "addiu", "andi", "xori", "ori", "slti", "sltiu"

    //map I1 op to binary

map<string,string> I_Type_1_op_map=create_I_Type_1_op_map();
    //000001 rs ??? imm
set<string> I_Type_2_op;
I_Type_2_op.insert("teqi");
I_Type_2_op.insert("tnei");
I_Type_2_op.insert("tgei");
I_Type_2_op.insert("tgeiu");
I_Type_2_op.insert("tlti");
I_Type_2_op.insert("tltiu");

        //"teqi", "tnei", "tgei", "tgeiu", "tlti", "tltiu"

    //map I2 ????? to binary

map<string,string> I_Type_2_nnnnn_map=create_I_Type_2_nnnnn_map();
    //op 00000 rt imm
    set<string> I_Type_3_op;
    I_Type_3_op.insert("lui");
        //"lui"

    //map I3 op to binary

map<string,string> I_Type_3_op_map=create_I_Type_3_op_map();

    //op rs rt offset(label)
set<string> Branch_Type_1_op;
Branch_Type_1_op.insert("bne");
Branch_Type_1_op.insert("beq");
        //"beq", "bne"


    //map B1 op to binary
map<string,string> Branch_Type_1_op_map=create_Branch_Type_1_op_map();
    //op rs ??? offset(label)
set<string> Branch_Type_2_op;
Branch_Type_2_op.insert("bgez");
Branch_Type_2_op.insert("bgezal");
Branch_Type_2_op.insert("bgtz");
Branch_Type_2_op.insert("blez");
Branch_Type_2_op.insert("bltezal");
Branch_Type_2_op.insert("bltz");
       // "bgez", "bgezal", "bgtz", "blez", "bltzal", "bltz"


map<string,string> Branch_Type_2_op_map=create_Branch_Type_2_op_map();

map<string,string> Branch_Type_2_nnnnn_map=create_Branch_Type_2_nnnnn_map();
    //op target
set<string> Jump_Type_1_op;
Jump_Type_1_op.insert("j");
Jump_Type_1_op.insert("jal");
        //"j", "jal"


map<string,string> Jump_Type_1_op_map=create_Jump_Type_1_op_map();
    //000000 rs 00000 rd 00000 001001
set<string> Jump_Type_2_op;
Jump_Type_1_op.insert("jalr");
        //"jalr"


    //000000 rs 000000000000000 1000
set<string> Jump_Type_3_op;
Jump_Type_3_op.insert(
        "jr"
    );
    //op rs rt offset(address)
set<string> Load_Type_1_op;
Load_Type_1_op.insert("lb");
Load_Type_1_op.insert("lbu");
Load_Type_1_op.insert("lh");
Load_Type_1_op.insert("lw");
Load_Type_1_op.insert("lwl");
Load_Type_1_op.insert("lwr");
Load_Type_1_op.insert("ll");
Load_Type_1_op.insert("sb");
Load_Type_1_op.insert("sh");
Load_Type_1_op.insert("sw");
Load_Type_1_op.insert("swl");
Load_Type_1_op.insert("swr");
Load_Type_1_op.insert("sc");
Load_Type_1_op.insert("lhu");



       // "lb", "lbu", "lh", "lhu", "lw", "lwl", "lwr", "ll",
   // "sb", "sh", "sw", "swl", "swr", "sc"



map<string,string> Load_Type_1_op_map=create_Load_Type_1_op_map();
    //000000 0000000000 rd ???
set<string> MF_Type_1_op;
MF_Type_1_op.insert("mflo");
MF_Type_1_op.insert("mfhi");
        //"mfhi", "mflo"


map<string,string> MF_Type_1_nnnnnn_map=create_MF_Type_1_nnnnnn_map();
    //000000 rs 000000000000000 ??????
set<string> MF_Type_2_op;
MF_Type_1_op.insert("mthi");
MF_Type_1_op.insert("mtlo");
        //"mthi", "mtlo"


map<string,string> MF_Type_2_nnnnnn_map=create_MF_Type_2_nnnnnn_map();
map<string,string> registerNumber=create_register_number_map();

/*string::size_type dollarpos, start;
start=0;
dollarpos=str.find("$");
Elementvector[0]=str.substr(0,dollarpos);*/

if(R_Type_1_op.find(ElementVector[0])!=R_Type_1_op.end()){
    start=dollarpos+1;
    
    cout<<"000000"<<registerNumber[ElementVector[2]]<<registerNumber[ElementVector[3]]<<registerNumber[ElementVector[1]]<<"00000"<<R_Type_1_funct_map[ElementVector[0]];
}
else if(R_Type_2_op.find(ElementVector[0])!=R_Type_2_op.end()){
    string shamt=decToBin(atoi(ElementVector[3].c_str()));
    cout<<"000000"<<"00000"<<registerNumber[ElementVector[2]]<<registerNumber[ElementVector[1]]<<setfill(shamt[0])<<setw(5)<<shamt<<R_Type_2_funct_map[ElementVector[0]];
}
else if(R_Type_3_op.find(ElementVector[0])!=R_Type_3_op.end()){
    cout<<"000000"<<registerNumber[ElementVector[1]]<<registerNumber[ElementVector[2]]<<"0000000000"<<R_Type_3_funct_map[ElementVector[0]];
}
else if(I_Type_1_op.find(ElementVector[0])!=I_Type_1_op.end()){
    string imm=decToBin(atoi(ElementVector[3].c_str()));
    cout<<I_Type_1_op_map[ElementVector[0]]<<registerNumber[ElementVector[2]]<<registerNumber[ElementVector[1]]<<setfill(imm[0])<<setw(16)<<imm;
}
else if(I_Type_2_op.find(ElementVector[0])!=I_Type_2_op.end()){
    string imm=decToBin(atoi(ElementVector[3].c_str()));
    cout<<"000001"<<registerNumber[ElementVector[1]]<<I_Type_2_nnnnn_map[ElementVector[0]]<<setfill(imm[0])<<setw(16)<<imm;
}
else if(Branch_Type_1_op.find(ElementVector[0])!=Branch_Type_1_op.end()){

    int offset=atoi(Labels[ElementVector[3]].c_str())-cur_address-1;

    string off_set=to_string(offset);
    cout<<Branch_Type_1_op_map[ElementVector[0]]<<registerNumber[ElementVector[1]]<<registerNumber[ElementVector[2]]<<setfill(off_set[0])<<setw(16)<<off_set;
}
else if(Branch_Type_2_op.find(ElementVector[0])!=Branch_Type_2_op.end()){

    int offset=atoi(Labels[ElementVector[2]].c_str())-cur_address-1;

    string off_set=to_string(offset);
    cout<<Branch_Type_2_op_map[ElementVector[0]]<<registerNumber[ElementVector[1]]<<Branch_Type_2_nnnnn_map[ElementVector[0]]<<setfill(off_set[0])<<setw(16)<<off_set;
}
else if(Jump_Type_1_op.find(ElementVector[0])!=Jump_Type_1_op.end()){
    string target=Labels[ElementVector[1]];
    cout<<Branch_Type_2_op_map[ElementVector[0]]<<registerNumber[ElementVector[1]]<<Branch_Type_2_nnnnn_map[ElementVector[0]]<<setfill(target[0])<<setw(26)<<target;
}
else if(Jump_Type_2_op.find(ElementVector[0])!=Jump_Type_2_op.end()){

    cout<<"000000"<<registerNumber[ElementVector[1]]<<"00000"<<registerNumber[ElementVector[2]]<<"00000"<<setfill(decToBin(9)[0])<<setw(6)<<decToBin(9);
}
else if(Jump_Type_3_op.find(ElementVector[0])!=Jump_Type_3_op.end()){

    cout<<"000000"<<registerNumber[ElementVector[1]]<<"000000000000000"<<setfill(decToBin(8)[0])<<setw(6)<<decToBin(8);
}
else if(Load_Type_1_op.find(ElementVector[0])!=Load_Type_1_op.end()){


    stringstream ss;
    string a=ElementVector[2];
       ss<<a;
       int i;
       ss>>i;//offset
       string offset=decToBin(i);
       string b;
       ss>>b;//rs

    cout<<Load_Type_1_op_map[ElementVector[0]]<<registerNumber[b]<<registerNumber[ElementVector[1]]<<setfill(offset[0])<<setw(16)<<offset;
}
else if(MF_Type_1_op.find(ElementVector[0])!=MF_Type_1_op.end()){


    cout<<"000000"<<"0000000000"<<registerNumber[ElementVector[1]]<<"00000"<<MF_Type_1_nnnnnn_map[ElementVector[0]];
}
else if(MF_Type_2_op.find(ElementVector[0])!=MF_Type_2_op.end()){


    cout<<"000000"<<registerNumber[ElementVector[1]]<<"000000000000000"<<MF_Type_2_nnnnnn_map[ElementVector[0]];
}
else
{
    cout<<"ungainly"<<endl;
}








    
    
    
    
}
void tokenize(string &str,string delim,vector<string>&out){
    string::size_type pos1,pos2;
    pos2=str.find(delim);
    pos1=0;
    if(pos2!=string::npos){
        if(pos2-pos1!=1){
            out.push_back(str.substr(pos1,pos2-pos1));
            pos1=pos2+delim.length();
        }
        if (pos1!=str.length()){
            out.push_back(str.substr(pos1));
        }
    }









}

void removeCommaAndCommentsAndBracket(string &a){
        /*string a="main: add 100($t1), $t2, $t3#comment#";*/

        for(unsigned j=0;j<a.size();j++){
            if ((a[j]==',')||(a[j]=='(')||(a[j]==')')){
                a.erase(a.begin()+j);
            }
        }
        string::size_type l=a.find('#');
        if (l!=string::npos){
            a.erase(l,a.length()-l);//单行或者复杂都可以
        }

    }






//decToBin(),tokenize(line,vector<>line elements,delimiter)
void findLabel( string&line, string&label,int&address_label){





    removeCommaAndCommentsAndBracket(line);
    vector<string> lineElements;
    tokenize(line," ",lineElements);
    if (lineElements.size()>0){
        ++address_label;
    }

    string::size_type n;
    n=line.find(":");
    if (n!=string::npos){
        label=line.substr(0,n);
    }


}
void createElementVector(string &line,vector<string> &Elementvector,int &cur_address/*当前行地址*/){
    vector<string>temp;
    removeCommaAndCommentsAndLabelAndBracket(line);
    tokenize(line," ",temp);

    if((temp.size()>0)){//排除空行



        Elementvector=temp;
        ++cur_address;



        }
    }


void printOut(vector<string>&ElementVector,map<string,string>&Labels,int cur_address){

    //000000 rs rt rd 00000 funct
set<string> R_Type_1_op;
R_Type_1_op.insert("add");
R_Type_1_op.insert("addu");
R_Type_1_op.insert("and");
R_Type_1_op.insert("nor");
R_Type_1_op.insert("or");
R_Type_1_op.insert("sllv");
R_Type_1_op.insert("srav");
R_Type_1_op.insert("srlv");
R_Type_1_op.insert("sub");
R_Type_1_op.insert("subv");
R_Type_1_op.insert("xor");
R_Type_1_op.insert("slt");
R_Type_1_op.insert("sltu");

                   /*, "addu", "and", "nor", "or", "sllv", "srav",
                    * "srlv", "sub", "subv", "xor", "slt", "sltu"});
    //map R1 funct to binary*/

map<string,string> R_Type_1_funct_map=create_R_Type_1_funct_map();

    //000000 rs rt rd shamt funct
set<string> R_Type_2_op;
R_Type_2_op.insert("sll");
R_Type_2_op.insert("sra");
R_Type_2_op.insert("srl");
        //"sll", "sra", "srl"

    //map R2 funct to binary

map<string,string> R_Type_2_funct_map=create_R_Type_2_funct_map();

    //000000 rs rt 0000000000 funct
set<string> R_Type_3_op;
R_Type_3_op.insert("div");
R_Type_3_op.insert("divu");
R_Type_3_op.insert("mult");
R_Type_3_op.insert("multu");
R_Type_3_op.insert("teq");
R_Type_3_op.insert("tne");
R_Type_3_op.insert("tge");
R_Type_3_op.insert("tgeu");
R_Type_3_op.insert("tlt");
R_Type_3_op.insert("tltu");

        /*"div", "divu", "mult", "multu", "teq", "tne", "tge", "tgeu",
    "tlt", "tltu"*/

    //map R3 funct to binary

map<string,string> R_Type_3_funct_map=create_R_Type_3_funct_map();
    //op rs rt imm
set<string> I_Type_1_op;
I_Type_1_op.insert("addi");
I_Type_1_op.insert("addiu");
I_Type_1_op.insert("andi");
I_Type_1_op.insert("xori");
I_Type_1_op.insert("ori");
I_Type_1_op.insert("slti");
I_Type_1_op.insert("sltiu");

        //"addi", "addiu", "andi", "xori", "ori", "slti", "sltiu"

    //map I1 op to binary

map<string,string> I_Type_1_op_map=create_I_Type_1_op_map();
    //000001 rs ??? imm
set<string> I_Type_2_op;
I_Type_2_op.insert("teqi");
I_Type_2_op.insert("tnei");
I_Type_2_op.insert("tgei");
I_Type_2_op.insert("tgeiu");
I_Type_2_op.insert("tlti");
I_Type_2_op.insert("tltiu");

        //"teqi", "tnei", "tgei", "tgeiu", "tlti", "tltiu"

    //map I2 ????? to binary

map<string,string> I_Type_2_nnnnn_map=create_I_Type_2_nnnnn_map();
    //op 00000 rt imm
    set<string> I_Type_3_op;
    I_Type_3_op.insert("lui");
        //"lui"

    //map I3 op to binary

map<string,string> I_Type_3_op_map=create_I_Type_3_op_map();

    //op rs rt offset(label)
set<string> Branch_Type_1_op;
Branch_Type_1_op.insert("bne");
Branch_Type_1_op.insert("beq");
        //"beq", "bne"


    //map B1 op to binary
map<string,string> Branch_Type_1_op_map=create_Branch_Type_1_op_map();
    //op rs ??? offset(label)
set<string> Branch_Type_2_op;
Branch_Type_2_op.insert("bgez");
Branch_Type_2_op.insert("bgezal");
Branch_Type_2_op.insert("bgtz");
Branch_Type_2_op.insert("blez");
Branch_Type_2_op.insert("bltezal");
Branch_Type_2_op.insert("bltz");
       // "bgez", "bgezal", "bgtz", "blez", "bltzal", "bltz"


map<string,string> Branch_Type_2_op_map=create_Branch_Type_2_op_map();

map<string,string> Branch_Type_2_nnnnn_map=create_Branch_Type_2_nnnnn_map();
    //op target
set<string> Jump_Type_1_op;
Jump_Type_1_op.insert("j");
Jump_Type_1_op.insert("jal");
        //"j", "jal"


map<string,string> Jump_Type_1_op_map=create_Jump_Type_1_op_map();
    //000000 rs 00000 rd 00000 001001
set<string> Jump_Type_2_op;
Jump_Type_1_op.insert("jalr");
        //"jalr"


    //000000 rs 000000000000000 1000
set<string> Jump_Type_3_op;
Jump_Type_3_op.insert(
        "jr"
    );
    //op rs rt offset(address)
set<string> Load_Type_1_op;
Load_Type_1_op.insert("lb");
Load_Type_1_op.insert("lbu");
Load_Type_1_op.insert("lh");
Load_Type_1_op.insert("lw");
Load_Type_1_op.insert("lwl");
Load_Type_1_op.insert("lwr");
Load_Type_1_op.insert("ll");
Load_Type_1_op.insert("sb");
Load_Type_1_op.insert("sh");
Load_Type_1_op.insert("sw");
Load_Type_1_op.insert("swl");
Load_Type_1_op.insert("swr");
Load_Type_1_op.insert("sc");
Load_Type_1_op.insert("lhu");



       // "lb", "lbu", "lh", "lhu", "lw", "lwl", "lwr", "ll",
   // "sb", "sh", "sw", "swl", "swr", "sc"



map<string,string> Load_Type_1_op_map=create_Load_Type_1_op_map();
    //000000 0000000000 rd ???
set<string> MF_Type_1_op;
MF_Type_1_op.insert("mflo");
MF_Type_1_op.insert("mfhi");
        //"mfhi", "mflo"


map<string,string> MF_Type_1_nnnnnn_map=create_MF_Type_1_nnnnnn_map();
    //000000 rs 000000000000000 ??????
set<string> MF_Type_2_op;
MF_Type_1_op.insert("mthi");
MF_Type_1_op.insert("mtlo");
        //"mthi", "mtlo"


map<string,string> MF_Type_2_nnnnnn_map=create_MF_Type_2_nnnnnn_map();
map<string,string> registerNumber=create_register_number_map();



if(R_Type_1_op.find(ElementVector[0])!=R_Type_1_op.end()){
    cout<<"000000"<<registerNumber[ElementVector[2]]<<registerNumber[ElementVector[3]]<<registerNumber[ElementVector[1]]<<"00000"<<R_Type_1_funct_map[ElementVector[0]];
}
else if(R_Type_2_op.find(ElementVector[0])!=R_Type_2_op.end()){
    string shamt=decToBin(atoi(ElementVector[3].c_str()));
    cout<<"000000"<<"00000"<<registerNumber[ElementVector[2]]<<registerNumber[ElementVector[1]]<<setfill(shamt[0])<<setw(5)<<shamt<<R_Type_2_funct_map[ElementVector[0]];
}
else if(R_Type_3_op.find(ElementVector[0])!=R_Type_3_op.end()){
    cout<<"000000"<<registerNumber[ElementVector[1]]<<registerNumber[ElementVector[2]]<<"0000000000"<<R_Type_3_funct_map[ElementVector[0]];
}
else if(I_Type_1_op.find(ElementVector[0])!=I_Type_1_op.end()){
    string imm=decToBin(atoi(ElementVector[3].c_str()));
    cout<<I_Type_1_op_map[ElementVector[0]]<<registerNumber[ElementVector[2]]<<registerNumber[ElementVector[1]]<<setfill(imm[0])<<setw(16)<<imm;
}
else if(I_Type_2_op.find(ElementVector[0])!=I_Type_2_op.end()){
    string imm=decToBin(atoi(ElementVector[3].c_str()));
    cout<<"000001"<<registerNumber[ElementVector[1]]<<I_Type_2_nnnnn_map[ElementVector[0]]<<setfill(imm[0])<<setw(16)<<imm;
}
else if(Branch_Type_1_op.find(ElementVector[0])!=Branch_Type_1_op.end()){

    int offset=atoi(Labels[ElementVector[3]].c_str())-cur_address-1;

    string off_set=to_string(offset);
    cout<<Branch_Type_1_op_map[ElementVector[0]]<<registerNumber[ElementVector[1]]<<registerNumber[ElementVector[2]]<<setfill(off_set[0])<<setw(16)<<off_set;
}
else if(Branch_Type_2_op.find(ElementVector[0])!=Branch_Type_2_op.end()){

    int offset=atoi(Labels[ElementVector[2]].c_str())-cur_address-1;

    string off_set=to_string(offset);
    cout<<Branch_Type_2_op_map[ElementVector[0]]<<registerNumber[ElementVector[1]]<<Branch_Type_2_nnnnn_map[ElementVector[0]]<<setfill(off_set[0])<<setw(16)<<off_set;
}
else if(Jump_Type_1_op.find(ElementVector[0])!=Jump_Type_1_op.end()){
    string target=Labels[ElementVector[1]];
    cout<<Branch_Type_2_op_map[ElementVector[0]]<<registerNumber[ElementVector[1]]<<Branch_Type_2_nnnnn_map[ElementVector[0]]<<setfill(target[0])<<setw(26)<<target;
}
else if(Jump_Type_2_op.find(ElementVector[0])!=Jump_Type_2_op.end()){

    cout<<"000000"<<registerNumber[ElementVector[1]]<<"00000"<<registerNumber[ElementVector[2]]<<"00000"<<setfill(decToBin(9)[0])<<setw(6)<<decToBin(9);
}
else if(Jump_Type_3_op.find(ElementVector[0])!=Jump_Type_3_op.end()){

    cout<<"000000"<<registerNumber[ElementVector[1]]<<"000000000000000"<<setfill(decToBin(8)[0])<<setw(6)<<decToBin(8);
}
else if(Load_Type_1_op.find(ElementVector[0])!=Load_Type_1_op.end()){


    stringstream ss;
    string a=ElementVector[2];
       ss<<a;
       int i;
       ss>>i;//offset
       string offset=decToBin(i);
       string b;
       ss>>b;//rs

    cout<<Load_Type_1_op_map[ElementVector[0]]<<registerNumber[b]<<registerNumber[ElementVector[1]]<<setfill(offset[0])<<setw(16)<<offset;
}
else if(MF_Type_1_op.find(ElementVector[0])!=MF_Type_1_op.end()){


    cout<<"000000"<<"0000000000"<<registerNumber[ElementVector[1]]<<"00000"<<MF_Type_1_nnnnnn_map[ElementVector[0]];
}
else if(MF_Type_2_op.find(ElementVector[0])!=MF_Type_2_op.end()){


    cout<<"000000"<<registerNumber[ElementVector[1]]<<"000000000000000"<<MF_Type_2_nnnnnn_map[ElementVector[0]];
}
else
{
    cout<<"ungainly"<<endl;
}










}
int main(){
    ifstream infile;

    string filename="/Users/shuxin/Desktop/3050input.txt";
    map<string,string>Labels;

    infile.open(filename.c_str());

    int address_label=0;
    string line;
    while(getline(infile,line)){

        


        
        
        /*cout<<endl;*/
        //cout<<line<<endl;
        string label;

        findLabel(line,label,address_label);
        Labels[label]=to_string(address_label);
        line="";
    }
    int cur_address=0;
    infile.close();
    infile.open(filename.c_str());
    string line_2;
    while(getline(infile,line_2)){
        vector<string> ElementVector;

        createElementVector(line_2,ElementVector,cur_address);

        printOut(ElementVector,Labels,cur_address);
        line_2="";

    }
    infile.close();

    return 0;

}
