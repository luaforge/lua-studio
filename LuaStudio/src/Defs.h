/*-----------------------------------------------------------------------------
	Lua Studio

Copyright (c) 1996-2008 Michal Kowalski
-----------------------------------------------------------------------------*/

#ifndef _asm_h_
#define _asm_h_

typedef unsigned int UINT32;		// liczba ca³kowita 32-bitowa bez znaku
typedef signed int SINT32;		// liczba ca³kowita 32-bitowa ze znakiem
typedef unsigned char UINT8;		// liczba ca³kowita 8-bitowa bez znaku
typedef unsigned short int UINT16;	// liczba ca³kowita 16-bitowa bez znaku


namespace Defs
{

/*
	enum Stat
	{
		STAT_INCLUDE = -999,
		STAT_REPEAT,
		STAT_ENDR,
		STAT_MACRO,
		STAT_ENDM,
		STAT_EXITM,
		STAT_IF_TRUE,
		STAT_IF_FALSE,
		STAT_IF_UNDETERMINED,
		STAT_ELSE,
		STAT_ENDIF,
		STAT_ASM,
		STAT_SKIP,
		STAT_USER_DEF_ERR,			// b³¹d u¿ytkownika (.ERROR)
		STAT_FIN,
		OK = 0,
		ERR_DAT,					// nieooczekiwane wyst¹pienie danych (tu tylko komentarz)
		ERR_UNEXP_DAT,				// nierozpoznany napis (na pocz¹tku wiersza)
		ERR_OUT_OF_MEM,
		ERR_FILE_READ,
		ERR_NUM_LONG,				// oczekiwana liczba max $FFFF
		ERR_NUM_NOT_BYTE,			// oczekiwana liczba max $FF
		ERR_NUM_NEGATIVE,			// oczekiwana wartoœæ nieujemna
		ERR_INSTR_OR_NULL_EXPECTED,	// oczekiwana instrukcja, komentarz lub CR
		ERR_IDX_REG_EXPECTED,		// oczekiwany rejestr indeksowy (X lub Y)
		ERR_IDX_REG_X_EXPECTED,		// oczekiwany rejestr indeksowy X
		ERR_IDX_REG_Y_EXPECTED,		// oczekiwany rejestr indeksowy Y
		ERR_COMMA_OR_BRACKET_EXPECTED,	// oczekiwany przecinek lub nawias ')'
		ERR_BRACKET_R_EXPECTED,		// oczekiwany nawias ')'
		ERR_BRACKET_L_EXPECTED,		// oczekiwany nawias '('
		ERR_DIV_BY_ZERO,			// dzielenie przez zero w wyra¿eniu
		ERR_EXPR_BRACKET_R_EXPECTED,// brak nawiasu ']' zamykaj¹cego wyra¿enie
		ERR_CONST_EXPECTED,			// oczekiwana sta³a (liczba lub ident)
		ERR_LABEL_REDEF,			// etykieta ju¿ zdefiniowana
		ERR_UNDEF_EXPR,				// nieokreœlona wartoœæ wyra¿enia
		ERR_PC_WRAPED,				// "przewiniêcie siê" licznika rozkazów
		ERR_UNDEF_LABEL,			// niezdefiniowana etykieta
		ERR_PHASE,					// b³¹d fazy - niezgodne wartoœci etykiety miêdzy przebiegami
		ERR_REL_OUT_OF_RNG,			// przekroczenie zakresu dla adresowania wzglêdnego
		ERR_MODE_NOT_ALLOWED,		// niedozwolony tryb adresowania
		ERR_STR_EXPECTED,			// oczekiwany ³añcuch znaków
		ERR_SPURIOUS_ENDIF,			// wyst¹pienie .ENDIF bez odpowiadaj¹cego mu .IF
		ERR_SPURIOUS_ELSE,			// wyst¹pienie .ELSE bez odpowiadaj¹cego mu .IF
		ERR_ENDIF_REQUIRED,			// brak dyrektywy .ENDIF
		ERR_LOCAL_LABEL_NOT_ALLOWED,// wymagane jest wyst¹pienie etykiety globalnej
		ERR_LABEL_EXPECTED,			// wymagana etykieta
		ERR_USER_ABORT,				// u¿ytkownik przerwa³ asemblacjê
		ERR_UNDEF_ORIGIN,			// brak dyrektywy .ORG
		ERR_MACRONAME_REQUIRED,		// brak etykiety nazywaj¹cej makrodefinicjê
		ERR_PARAM_ID_REDEF,			// nazwa parametru ju¿ zdefiniowana
		ERR_NESTED_MACRO,			// definicja makra w makrodefinicji jest zabroniona
		ERR_ENDM_REQUIRED,			// brak dyrektywy .ENDM
		ERR_UNKNOWN_INSTR,			// nierozpoznana nazwa makra/instrukcji/dyrektywy
		ERR_PARAM_REQUIRED,			// brak wymaganej iloœci parametrów wywo³ania makra
		ERR_SPURIOUS_ENDM,			// wyst¹pienie .ENDM bez odpowiadaj¹cego mu .MACRO
		ERR_SPURIOUS_EXITM,			// wyst¹pienie .EXIT poza makrodefinicj¹ jest niedozwolone
		ERR_STR_NOT_ALLOWED,		// wyra¿enie znakowe niedozwolone
		ERR_NOT_STR_PARAM,			// parametr wo³any z '$' nie posiada wartoœci typu tekstowego
		ERR_EMPTY_PARAM,			// wo³any parametr nie istnieje (za du¿y nr przy odwo³aniu: %num)
		ERR_UNDEF_PARAM_NUMBER,		// numer parametru w wywo³aniu "%number" jest niezdefiniowany
		ERR_BAD_MACRONAME,			// nazwa makra nie mo¿e zaczynaæ siê od znaku '.'
		ERR_PARAM_NUMBER_EXPECTED,	// oczekiwany numer parametru makra
		ERR_LABEL_NOT_ALLOWED,		// niedozwolone wyst¹pienie etykiety (przed dyrektyw¹)
		ERR_BAD_REPT_NUM,			// b³¹dna iloœæ powtórzeñ (dozwolone od 0 do 0xFFFF)
		ERR_SPURIOUS_ENDR,			// wyst¹pienie .ENDR bez odpowiadaj¹cego mu .REPEAT
		ERR_INCLUDE_NOT_ALLOWED,	// dyrektywa .INCLUDE nie mo¿e wystêpowaæ w makrach i powtórkach
		ERR_STRING_TOO_LONG,		// za d³ugi ³añcuch (w .STR)
		ERR_NOT_BIT_NUM,			// oczekiwana liczba od 0 do 7 (numer biru)
		ERR_OPT_NAME_REQUIRED,		// brak nazwy opcji
		ERR_OPT_NAME_UNKNOWN,		// nierozpoznana nazwa opcji
		ERR_LINE_TO_LONG,			// za d³ugi wiersz Ÿród³owy
		ERR_PARAM_DEF_REQUIRED,		// wymagana nazwa parametru makra
		ERR_INDIRECT_BYTE_EXPECTED,	// Indirect postindexed addressing mode requires byte operand
		ERR_CONST_LABEL_REDEF,		// Constant label (predefined) cannot be redefined
		ERR_NO_RANGE,				// expected valid range: first value has to be less than or equal to snd value
		ERR_NUM_ZERO,				// expected nonzero value

		ERR_LAST					// ostatnia wartoœæ typu Stat - nie b³¹d
	};

	enum OpCode		// rodzaj instrukcji procesora
	{
		C_LDA, C_LDX, C_LDY,
		C_STA, C_STX, C_STY, C_STZ,
		C_TAX, C_TXA, C_TAY, C_TYA, C_TXS, C_TSX,
		C_ADC, C_SBC, C_CMP, C_CPX, C_CPY,
		C_INC, C_DEC, C_INA, C_DEA, C_INX, C_DEX, C_INY, C_DEY,
		C_ASL, C_LSR, C_ROL, C_ROR,
		C_AND, C_ORA, C_EOR,
		C_BIT, C_TSB, C_TRB,
		C_JMP, C_JSR, C_BRK,
		C_BRA, C_BPL, C_BMI, C_BVC, C_BVS, C_BCC, C_BCS, C_BNE, C_BEQ,
		C_RTS, C_RTI,
		C_PHA, C_PLA, C_PHX, C_PLX, C_PHY, C_PLY, C_PHP, C_PLP,
		C_CLC, C_SEC, C_CLV, C_CLD, C_SED, C_CLI, C_SEI,
		C_NOP,
		// nowe rozkazy z 6501
		C_BBR, //C_BBR1, C_BBR2, C_BBR3, C_BBR4, C_BBR5, C_BBR6, C_BBR7,
		C_BBS, //C_BBS1, C_BBS2, C_BBS3, C_BBS4, C_BBS5, C_BBS6, C_BBS7,
		C_RMB, //C_RMB1, C_RMB2, C_RMB3, C_RMB4, C_RMB5, C_RMB6, C_RMB7,
		C_SMB, //C_SMB1, C_SMB2, C_SMB3, C_SMB4, C_SMB5, C_SMB6, C_SMB7,

		C_ILL		// wartoœæ do oznaczania nielegalnych rozkazów w symulatorze (ILLEGAL)
		// jednoczeœnie wartoœæ maksymalna dla typu OpCode
	};

	enum CodeAdr	// tryby adresowania
	{
		A_IMP,		// implied
		A_ACC,		// accumulator
		A_IMM,		// immediate
		A_ZPG,		// zero page
		A_ABS,		// absolute
		A_ABS_X,	// absolute indexed X
		A_ABS_Y,	// absolute indexed Y
		A_ZPG_X,	// zero page indexed X
		A_ZPG_Y,	// zero page indexed Y
		A_REL,		// relative
		A_ZPGI,		// zero page indirect
		A_ZPGI_X,	// zero page indirect, indexed X
		A_ZPGI_Y,	// zero page indirect, indexed Y
		A_ABSI,		// absolute indirect
		A_ABSI_X,	// absolute indirect, indexed X
		A_ZREL,		// zero page / relative -> BBS i BBR z 6501
		A_ZPG2,		// zero page dla rozkazów RMB SMB z 6501

		A_NO_OF_MODES,	// iloœæ trybów adresowania

		A_ABS_OR_ZPG= A_NO_OF_MODES,	// niezdeterminowany tryb adresowania
		A_ABSX_OR_ZPGX,
		A_ABSY_OR_ZPGY,
		A_ABSI_OR_ZPGI,
		A_IMP_OR_ACC,
		A_ABSIX_OR_ZPGIX,

		A_IMP2,	// implied dla rozkazu BRK

		A_ILL		// wartoœæ do oznaczania nielegalnych rozkazów w symulatorze (ILLEGAL)
	};

	enum InstrType	// rodzaj dyrektywy asemblera
	{
		I_ORG,		// origin
		I_DB,		// def byte
		I_DW,		// def word
		I_DD,		// def double byte
		I_DS,		// def string
		I_ASCIS,	// ascii + $80
		I_DCB,		// declare block
		I_RS,		// reserve space
		I_END,		// zakoñcz asemblacjê
		I_ERROR,	// zg³oszenie b³êdu
		I_INCLUDE,	// w³¹czenie pliku
		I_IF,		// asemblacja warunkowa
		I_ELSE,
		I_ENDIF,
		I_MACRO,	// makrodefinicja
		I_EXITM,
		I_ENDM,
		I_START,	// pocz¹tek programu dla symulatora
		I_SET,		// przypisanie wartoœci
		I_REPEAT,	// powtórka
		I_ENDR,
		I_OPT,		// opcje asemblera
		I_ROM_AREA,	// protected memory area
		I_IO_WND	// size of I/O window (columns, rows)
	};

	enum OperType		// typ operatora
	{
		O_HI, O_LO,
		O_B_AND, O_B_OR, O_B_XOR, O_B_NOT,
		O_PLUS, O_MINUS, O_DIV, O_MUL, O_MOD,
		O_AND, O_OR, O_NOT,
		O_EQ, O_NE, O_GT, O_LT, O_GTE, O_LTE,
		O_SHL, O_SHR
	};

	static const TCHAR LOCAL_LABEL_CHAR;	// znak rozpoczynaj¹cy etykietê lokaln¹
	static const TCHAR MULTIPARAM[];		// wielokropek - dowolna iloœæ parametrów

	enum Msg
	{
		WM_USER_GET_NEXT_LINE = WM_USER+4000, // pobranie/udostêpnienie kolejnego wiersza
		WM_USER_GET_LINE_NO,		// pobranie numeru aktualnego wiersza
		WM_USER_FIN,				// poinformowanie o zakoñczeniu asemblacji
		WM_USER_GET_TITLE,			// odczyt nazwy dokumentu
		WM_USER_NEXT_PASS,			// nastêpny przebieg asemblacji
		WM_USER_ABORT_ASM			// przerwanie asemblacji
	};
*/
	enum SymStat
	{
		SYM_OK = 0,
		SYM_BPT_EXECUTE,		// przerwanie przy wykonaniu
		SYM_BPT_READ,			// przerwanie przy odczycie
		SYM_BPT_WRITE,			// przerwanie przy zapisie
		SYM_BPT_TEMP,			// przerwanie przy wykonaniu
		SYM_ILLEGAL_CODE,		// napotkana nielegalna instrukcja
		SYM_STOP,				// program zatrzymany przez u¿ytkownika
		SYM_FIN,				// program zakoñczony
		SYM_RUN,				// program uruchomiony
		SYM_INP_WAIT,			// waiting for data input
		SYM_ILL_WRITE			// protected area writing attempt detected
	};

	enum Breakpoint
	{
		BPT_NONE	= 0x00,		// nie ma przerwania
		BPT_EXECUTE	= 0x01,		// przerwanie przy wykonaniu
		BPT_READ	= 0x02,		// przerwanie przy odczycie
		BPT_WRITE	= 0x04,		// przerwanie przy zapisie
		BPT_MASK	= 0x07,
		BPT_NO_CODE	= 0x08,		// wiersz nie zawiera kodu - przerwanie nie mo¿e byæ ustawione
		BPT_TEMP_EXEC=0x10,		// przerwanie tymczasowe do zatrzymania programu
		BPT_DISABLED= 0x80		// przerwanie wy³¹czone
	};
/*
	enum Finish				// sposób zakoñczenia programu
	{
		FIN_BY_BRK,			// po napotkaniu instrukcji BRK
		FIN_BY_RTS,			// po napotkaniu RTS przy pustym stosie
		FIN_BY_BB			// po napotkaniu kodu $BB
	};

	enum DeasmFmt				// format deasemblacji
	{
		DF_NONE		  = 0x00,
		DF_ADDRESS	  = 0x01,	// adres przed instrukcj¹
		DF_CODE_BYTES = 0x02,	// przed instrukcj¹ jej kod i argumenty
		DF_BRANCH_INFO= 0x04,	// za rozkazami skoków warunkowych info czy skok aktywny
		DF_LABELS	  = 0x08,	// adresy argumentów poprzedzone liter¹ 'a' lub 'z'
		DF_HELP		  = 0x10,	// generate output suitable for dynamic help
		DF_USE_BRK	  = 0x20,	// generate BRK instead of .DB 0
		DF_65C02	  = 0x40	// use 65c02 instead of current settings
	};
*/
	//............................... debug info ................................

	typedef UINT16 FileUID;

	enum DbgFlag
	{
		DBG_EMPTY	= 0,
		DBG_CODE	= 1,
		DBG_DATA	= 2,
		DBG_MACRO	= 4,
	};

};


//CAsm::DeasmFmt inline operator | (CAsm::DeasmFmt f1, CAsm::DeasmFmt f2)
//{
//	return static_cast<CAsm::DeasmFmt>(DWORD(f1) | DWORD(f2));
//}


#endif
