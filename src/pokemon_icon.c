#include "global.h"
#include "graphics.h"
#include "mail.h"
#include "palette.h"
#include "pokemon_debug.h"
#include "pokemon_icon.h"
#include "sprite.h"
#include "data.h"

#define POKE_ICON_BASE_PAL_TAG 56000

struct MonIconSpriteTemplate
{
    const struct OamData *oam;
    const u8 *image;
    const union AnimCmd *const *anims;
    const union AffineAnimCmd *const *affineAnims;
    void (*callback)(struct Sprite *);
    u16 paletteTag;
};

static u8 CreateMonIconSprite(struct MonIconSpriteTemplate *, s16, s16, u8);
static void FreeAndDestroyMonIconSprite_(struct Sprite *sprite);

extern const u8 gMonIcon_QuestionMark[];

// Kept this commented out table to keep PoryMap compatibility.
/*
const u8 *const gMonIconTable[NUM_SPECIES + 1] =
{
    [SPECIES_NONE] = gMonIcon_QuestionMark,
    [SPECIES_BULBASAUR] = gMonIcon_Bulbasaur,
    [SPECIES_IVYSAUR] = gMonIcon_Ivysaur,
    [SPECIES_VENUSAUR] = gMonIcon_Venusaur,
    [SPECIES_CHARMANDER] = gMonIcon_Charmander,
    [SPECIES_CHARMELEON] = gMonIcon_Charmeleon,
    [SPECIES_CHARIZARD] = gMonIcon_Charizard,
    [SPECIES_SQUIRTLE] = gMonIcon_Squirtle,
    [SPECIES_WARTORTLE] = gMonIcon_Wartortle,
    [SPECIES_BLASTOISE] = gMonIcon_Blastoise,
    [SPECIES_CATERPIE] = gMonIcon_Caterpie,
    [SPECIES_METAPOD] = gMonIcon_Metapod,
    [SPECIES_BUTTERFREE] = gMonIcon_Butterfree,
    [SPECIES_WEEDLE] = gMonIcon_Weedle,
    [SPECIES_KAKUNA] = gMonIcon_Kakuna,
    [SPECIES_BEEDRILL] = gMonIcon_Beedrill,
    [SPECIES_PIDGEY] = gMonIcon_Pidgey,
    [SPECIES_PIDGEOTTO] = gMonIcon_Pidgeotto,
    [SPECIES_PIDGEOT] = gMonIcon_Pidgeot,
    [SPECIES_RATTATA] = gMonIcon_Rattata,
    [SPECIES_RATICATE] = gMonIcon_Raticate,
    [SPECIES_SPEAROW] = gMonIcon_Spearow,
    [SPECIES_FEAROW] = gMonIcon_Fearow,
    [SPECIES_EKANS] = gMonIcon_Ekans,
    [SPECIES_ARBOK] = gMonIcon_Arbok,
    [SPECIES_PIKACHU] = gMonIcon_Pikachu,
    [SPECIES_RAICHU] = gMonIcon_Raichu,
    [SPECIES_SANDSHREW] = gMonIcon_Sandshrew,
    [SPECIES_SANDSLASH] = gMonIcon_Sandslash,
    [SPECIES_NIDORAN_F] = gMonIcon_NidoranF,
    [SPECIES_NIDORINA] = gMonIcon_Nidorina,
    [SPECIES_NIDOQUEEN] = gMonIcon_Nidoqueen,
    [SPECIES_NIDORAN_M] = gMonIcon_NidoranM,
    [SPECIES_NIDORINO] = gMonIcon_Nidorino,
    [SPECIES_NIDOKING] = gMonIcon_Nidoking,
    [SPECIES_CLEFAIRY] = gMonIcon_Clefairy,
    [SPECIES_CLEFABLE] = gMonIcon_Clefable,
    [SPECIES_VULPIX] = gMonIcon_Vulpix,
    [SPECIES_NINETALES] = gMonIcon_Ninetales,
    [SPECIES_JIGGLYPUFF] = gMonIcon_Jigglypuff,
    [SPECIES_WIGGLYTUFF] = gMonIcon_Wigglytuff,
    [SPECIES_ZUBAT] = gMonIcon_Zubat,
    [SPECIES_GOLBAT] = gMonIcon_Golbat,
    [SPECIES_ODDISH] = gMonIcon_Oddish,
    [SPECIES_GLOOM] = gMonIcon_Gloom,
    [SPECIES_VILEPLUME] = gMonIcon_Vileplume,
    [SPECIES_PARAS] = gMonIcon_Paras,
    [SPECIES_PARASECT] = gMonIcon_Parasect,
    [SPECIES_VENONAT] = gMonIcon_Venonat,
    [SPECIES_VENOMOTH] = gMonIcon_Venomoth,
    [SPECIES_DIGLETT] = gMonIcon_Diglett,
    [SPECIES_DUGTRIO] = gMonIcon_Dugtrio,
    [SPECIES_MEOWTH] = gMonIcon_Meowth,
    [SPECIES_PERSIAN] = gMonIcon_Persian,
    [SPECIES_PSYDUCK] = gMonIcon_Psyduck,
    [SPECIES_GOLDUCK] = gMonIcon_Golduck,
    [SPECIES_MANKEY] = gMonIcon_Mankey,
    [SPECIES_PRIMEAPE] = gMonIcon_Primeape,
    [SPECIES_GROWLITHE] = gMonIcon_Growlithe,
    [SPECIES_ARCANINE] = gMonIcon_Arcanine,
    [SPECIES_POLIWAG] = gMonIcon_Poliwag,
    [SPECIES_POLIWHIRL] = gMonIcon_Poliwhirl,
    [SPECIES_POLIWRATH] = gMonIcon_Poliwrath,
    [SPECIES_ABRA] = gMonIcon_Abra,
    [SPECIES_KADABRA] = gMonIcon_Kadabra,
    [SPECIES_ALAKAZAM] = gMonIcon_Alakazam,
    [SPECIES_MACHOP] = gMonIcon_Machop,
    [SPECIES_MACHOKE] = gMonIcon_Machoke,
    [SPECIES_MACHAMP] = gMonIcon_Machamp,
    [SPECIES_BELLSPROUT] = gMonIcon_Bellsprout,
    [SPECIES_WEEPINBELL] = gMonIcon_Weepinbell,
    [SPECIES_VICTREEBEL] = gMonIcon_Victreebel,
    [SPECIES_TENTACOOL] = gMonIcon_Tentacool,
    [SPECIES_TENTACRUEL] = gMonIcon_Tentacruel,
    [SPECIES_GEODUDE] = gMonIcon_Geodude,
    [SPECIES_GRAVELER] = gMonIcon_Graveler,
    [SPECIES_GOLEM] = gMonIcon_Golem,
    [SPECIES_PONYTA] = gMonIcon_Ponyta,
    [SPECIES_RAPIDASH] = gMonIcon_Rapidash,
    [SPECIES_SLOWPOKE] = gMonIcon_Slowpoke,
    [SPECIES_SLOWBRO] = gMonIcon_Slowbro,
    [SPECIES_MAGNEMITE] = gMonIcon_Magnemite,
    [SPECIES_MAGNETON] = gMonIcon_Magneton,
    [SPECIES_FARFETCHD] = gMonIcon_Farfetchd,
    [SPECIES_DODUO] = gMonIcon_Doduo,
    [SPECIES_DODRIO] = gMonIcon_Dodrio,
    [SPECIES_SEEL] = gMonIcon_Seel,
    [SPECIES_DEWGONG] = gMonIcon_Dewgong,
    [SPECIES_GRIMER] = gMonIcon_Grimer,
    [SPECIES_MUK] = gMonIcon_Muk,
    [SPECIES_SHELLDER] = gMonIcon_Shellder,
    [SPECIES_CLOYSTER] = gMonIcon_Cloyster,
    [SPECIES_GASTLY] = gMonIcon_Gastly,
    [SPECIES_HAUNTER] = gMonIcon_Haunter,
    [SPECIES_GENGAR] = gMonIcon_Gengar,
    [SPECIES_ONIX] = gMonIcon_Onix,
    [SPECIES_DROWZEE] = gMonIcon_Drowzee,
    [SPECIES_HYPNO] = gMonIcon_Hypno,
    [SPECIES_KRABBY] = gMonIcon_Krabby,
    [SPECIES_KINGLER] = gMonIcon_Kingler,
    [SPECIES_VOLTORB] = gMonIcon_Voltorb,
    [SPECIES_ELECTRODE] = gMonIcon_Electrode,
    [SPECIES_EXEGGCUTE] = gMonIcon_Exeggcute,
    [SPECIES_EXEGGUTOR] = gMonIcon_Exeggutor,
    [SPECIES_CUBONE] = gMonIcon_Cubone,
    [SPECIES_MAROWAK] = gMonIcon_Marowak,
    [SPECIES_HITMONLEE] = gMonIcon_Hitmonlee,
    [SPECIES_HITMONCHAN] = gMonIcon_Hitmonchan,
    [SPECIES_LICKITUNG] = gMonIcon_Lickitung,
    [SPECIES_KOFFING] = gMonIcon_Koffing,
    [SPECIES_WEEZING] = gMonIcon_Weezing,
    [SPECIES_RHYHORN] = gMonIcon_Rhyhorn,
    [SPECIES_RHYDON] = gMonIcon_Rhydon,
    [SPECIES_CHANSEY] = gMonIcon_Chansey,
    [SPECIES_TANGELA] = gMonIcon_Tangela,
    [SPECIES_KANGASKHAN] = gMonIcon_Kangaskhan,
    [SPECIES_HORSEA] = gMonIcon_Horsea,
    [SPECIES_SEADRA] = gMonIcon_Seadra,
    [SPECIES_GOLDEEN] = gMonIcon_Goldeen,
    [SPECIES_SEAKING] = gMonIcon_Seaking,
    [SPECIES_STARYU] = gMonIcon_Staryu,
    [SPECIES_STARMIE] = gMonIcon_Starmie,
    [SPECIES_MR_MIME] = gMonIcon_MrMime,
    [SPECIES_SCYTHER] = gMonIcon_Scyther,
    [SPECIES_JYNX] = gMonIcon_Jynx,
    [SPECIES_ELECTABUZZ] = gMonIcon_Electabuzz,
    [SPECIES_MAGMAR] = gMonIcon_Magmar,
    [SPECIES_PINSIR] = gMonIcon_Pinsir,
    [SPECIES_TAUROS] = gMonIcon_Tauros,
    [SPECIES_TAUROS_PALDEAN_COMBAT_BREED] = gMonIcon_TaurosPaldeanCombatBreed,
    [SPECIES_TAUROS_PALDEAN_BLAZE_BREED] = gMonIcon_TaurosPaldeanBlazeBreed,
    [SPECIES_TAUROS_PALDEAN_AQUA_BREED] = gMonIcon_TaurosPaldeanAquaBreed,
    [SPECIES_MAGIKARP] = gMonIcon_Magikarp,
    [SPECIES_GYARADOS] = gMonIcon_Gyarados,
    [SPECIES_LAPRAS] = gMonIcon_Lapras,
    [SPECIES_DITTO] = gMonIcon_Ditto,
    [SPECIES_EEVEE] = gMonIcon_Eevee,
    [SPECIES_VAPOREON] = gMonIcon_Vaporeon,
    [SPECIES_JOLTEON] = gMonIcon_Jolteon,
    [SPECIES_FLAREON] = gMonIcon_Flareon,
    [SPECIES_PORYGON] = gMonIcon_Porygon,
    [SPECIES_OMANYTE] = gMonIcon_Omanyte,
    [SPECIES_OMASTAR] = gMonIcon_Omastar,
    [SPECIES_KABUTO] = gMonIcon_Kabuto,
    [SPECIES_KABUTOPS] = gMonIcon_Kabutops,
    [SPECIES_AERODACTYL] = gMonIcon_Aerodactyl,
    [SPECIES_SNORLAX] = gMonIcon_Snorlax,
    [SPECIES_ARTICUNO] = gMonIcon_Articuno,
    [SPECIES_ZAPDOS] = gMonIcon_Zapdos,
    [SPECIES_MOLTRES] = gMonIcon_Moltres,
    [SPECIES_DRATINI] = gMonIcon_Dratini,
    [SPECIES_DRAGONAIR] = gMonIcon_Dragonair,
    [SPECIES_DRAGONITE] = gMonIcon_Dragonite,
    [SPECIES_MEWTWO] = gMonIcon_Mewtwo,
    [SPECIES_MEW] = gMonIcon_Mew,
    [SPECIES_CHIKORITA] = gMonIcon_Chikorita,
    [SPECIES_BAYLEEF] = gMonIcon_Bayleef,
    [SPECIES_MEGANIUM] = gMonIcon_Meganium,
    [SPECIES_CYNDAQUIL] = gMonIcon_Cyndaquil,
    [SPECIES_QUILAVA] = gMonIcon_Quilava,
    [SPECIES_TYPHLOSION] = gMonIcon_Typhlosion,
    [SPECIES_TOTODILE] = gMonIcon_Totodile,
    [SPECIES_CROCONAW] = gMonIcon_Croconaw,
    [SPECIES_FERALIGATR] = gMonIcon_Feraligatr,
    [SPECIES_SENTRET] = gMonIcon_Sentret,
    [SPECIES_FURRET] = gMonIcon_Furret,
    [SPECIES_HOOTHOOT] = gMonIcon_Hoothoot,
    [SPECIES_NOCTOWL] = gMonIcon_Noctowl,
    [SPECIES_LEDYBA] = gMonIcon_Ledyba,
    [SPECIES_LEDIAN] = gMonIcon_Ledian,
    [SPECIES_SPINARAK] = gMonIcon_Spinarak,
    [SPECIES_ARIADOS] = gMonIcon_Ariados,
    [SPECIES_CROBAT] = gMonIcon_Crobat,
    [SPECIES_CHINCHOU] = gMonIcon_Chinchou,
    [SPECIES_LANTURN] = gMonIcon_Lanturn,
    [SPECIES_PICHU] = gMonIcon_Pichu,
    [SPECIES_CLEFFA] = gMonIcon_Cleffa,
    [SPECIES_IGGLYBUFF] = gMonIcon_Igglybuff,
    [SPECIES_TOGEPI] = gMonIcon_Togepi,
    [SPECIES_TOGETIC] = gMonIcon_Togetic,
    [SPECIES_NATU] = gMonIcon_Natu,
    [SPECIES_XATU] = gMonIcon_Xatu,
    [SPECIES_MAREEP] = gMonIcon_Mareep,
    [SPECIES_FLAAFFY] = gMonIcon_Flaaffy,
    [SPECIES_AMPHAROS] = gMonIcon_Ampharos,
    [SPECIES_BELLOSSOM] = gMonIcon_Bellossom,
    [SPECIES_MARILL] = gMonIcon_Marill,
    [SPECIES_AZUMARILL] = gMonIcon_Azumarill,
    [SPECIES_SUDOWOODO] = gMonIcon_Sudowoodo,
    [SPECIES_POLITOED] = gMonIcon_Politoed,
    [SPECIES_HOPPIP] = gMonIcon_Hoppip,
    [SPECIES_SKIPLOOM] = gMonIcon_Skiploom,
    [SPECIES_JUMPLUFF] = gMonIcon_Jumpluff,
    [SPECIES_AIPOM] = gMonIcon_Aipom,
    [SPECIES_SUNKERN] = gMonIcon_Sunkern,
    [SPECIES_SUNFLORA] = gMonIcon_Sunflora,
    [SPECIES_YANMA] = gMonIcon_Yanma,
    [SPECIES_WOOPER] = gMonIcon_Wooper,
    //[SPECIES_WOOPER_PALDEAN] = gMonIcon_WooperPaldean,
    [SPECIES_QUAGSIRE] = gMonIcon_Quagsire,
    [SPECIES_ESPEON] = gMonIcon_Espeon,
    [SPECIES_UMBREON] = gMonIcon_Umbreon,
    [SPECIES_MURKROW] = gMonIcon_Murkrow,
    [SPECIES_SLOWKING] = gMonIcon_Slowking,
    [SPECIES_MISDREAVUS] = gMonIcon_Misdreavus,
    [SPECIES_UNOWN] = gMonIcon_UnownA,
    [SPECIES_WOBBUFFET] = gMonIcon_Wobbuffet,
    [SPECIES_GIRAFARIG] = gMonIcon_Girafarig,
    [SPECIES_PINECO] = gMonIcon_Pineco,
    [SPECIES_FORRETRESS] = gMonIcon_Forretress,
    [SPECIES_DUNSPARCE] = gMonIcon_Dunsparce,
    [SPECIES_GLIGAR] = gMonIcon_Gligar,
    [SPECIES_STEELIX] = gMonIcon_Steelix,
    [SPECIES_SNUBBULL] = gMonIcon_Snubbull,
    [SPECIES_GRANBULL] = gMonIcon_Granbull,
    [SPECIES_QWILFISH] = gMonIcon_Qwilfish,
    [SPECIES_SCIZOR] = gMonIcon_Scizor,
    [SPECIES_SHUCKLE] = gMonIcon_Shuckle,
    [SPECIES_HERACROSS] = gMonIcon_Heracross,
    [SPECIES_SNEASEL] = gMonIcon_Sneasel,
    [SPECIES_TEDDIURSA] = gMonIcon_Teddiursa,
    [SPECIES_URSARING] = gMonIcon_Ursaring,
    [SPECIES_SLUGMA] = gMonIcon_Slugma,
    [SPECIES_MAGCARGO] = gMonIcon_Magcargo,
    [SPECIES_SWINUB] = gMonIcon_Swinub,
    [SPECIES_PILOSWINE] = gMonIcon_Piloswine,
    [SPECIES_CORSOLA] = gMonIcon_Corsola,
    [SPECIES_REMORAID] = gMonIcon_Remoraid,
    [SPECIES_OCTILLERY] = gMonIcon_Octillery,
    [SPECIES_DELIBIRD] = gMonIcon_Delibird,
    [SPECIES_MANTINE] = gMonIcon_Mantine,
    [SPECIES_SKARMORY] = gMonIcon_Skarmory,
    [SPECIES_HOUNDOUR] = gMonIcon_Houndour,
    [SPECIES_HOUNDOOM] = gMonIcon_Houndoom,
    [SPECIES_KINGDRA] = gMonIcon_Kingdra,
    [SPECIES_PHANPY] = gMonIcon_Phanpy,
    [SPECIES_DONPHAN] = gMonIcon_Donphan,
    [SPECIES_PORYGON2] = gMonIcon_Porygon2,
    [SPECIES_STANTLER] = gMonIcon_Stantler,
    [SPECIES_SMEARGLE] = gMonIcon_Smeargle,
    [SPECIES_TYROGUE] = gMonIcon_Tyrogue,
    [SPECIES_HITMONTOP] = gMonIcon_Hitmontop,
    [SPECIES_SMOOCHUM] = gMonIcon_Smoochum,
    [SPECIES_ELEKID] = gMonIcon_Elekid,
    [SPECIES_MAGBY] = gMonIcon_Magby,
    [SPECIES_MILTANK] = gMonIcon_Miltank,
    [SPECIES_BLISSEY] = gMonIcon_Blissey,
    [SPECIES_RAIKOU] = gMonIcon_Raikou,
    [SPECIES_ENTEI] = gMonIcon_Entei,
    [SPECIES_SUICUNE] = gMonIcon_Suicune,
    [SPECIES_LARVITAR] = gMonIcon_Larvitar,
    [SPECIES_PUPITAR] = gMonIcon_Pupitar,
    [SPECIES_TYRANITAR] = gMonIcon_Tyranitar,
    [SPECIES_LUGIA] = gMonIcon_Lugia,
    [SPECIES_HO_OH] = gMonIcon_HoOh,
    [SPECIES_CELEBI] = gMonIcon_Celebi,
    [SPECIES_TREECKO] = gMonIcon_Treecko,
    [SPECIES_GROVYLE] = gMonIcon_Grovyle,
    [SPECIES_SCEPTILE] = gMonIcon_Sceptile,
    [SPECIES_TORCHIC] = gMonIcon_Torchic,
    [SPECIES_COMBUSKEN] = gMonIcon_Combusken,
    [SPECIES_BLAZIKEN] = gMonIcon_Blaziken,
    [SPECIES_MUDKIP] = gMonIcon_Mudkip,
    [SPECIES_MARSHTOMP] = gMonIcon_Marshtomp,
    [SPECIES_SWAMPERT] = gMonIcon_Swampert,
    [SPECIES_POOCHYENA] = gMonIcon_Poochyena,
    [SPECIES_MIGHTYENA] = gMonIcon_Mightyena,
    [SPECIES_ZIGZAGOON] = gMonIcon_Zigzagoon,
    [SPECIES_LINOONE] = gMonIcon_Linoone,
    [SPECIES_WURMPLE] = gMonIcon_Wurmple,
    [SPECIES_SILCOON] = gMonIcon_Silcoon,
    [SPECIES_BEAUTIFLY] = gMonIcon_Beautifly,
    [SPECIES_CASCOON] = gMonIcon_Cascoon,
    [SPECIES_DUSTOX] = gMonIcon_Dustox,
    [SPECIES_LOTAD] = gMonIcon_Lotad,
    [SPECIES_LOMBRE] = gMonIcon_Lombre,
    [SPECIES_LUDICOLO] = gMonIcon_Ludicolo,
    [SPECIES_SEEDOT] = gMonIcon_Seedot,
    [SPECIES_NUZLEAF] = gMonIcon_Nuzleaf,
    [SPECIES_SHIFTRY] = gMonIcon_Shiftry,
    [SPECIES_NINCADA] = gMonIcon_Nincada,
    [SPECIES_NINJASK] = gMonIcon_Ninjask,
    [SPECIES_SHEDINJA] = gMonIcon_Shedinja,
    [SPECIES_TAILLOW] = gMonIcon_Taillow,
    [SPECIES_SWELLOW] = gMonIcon_Swellow,
    [SPECIES_SHROOMISH] = gMonIcon_Shroomish,
    [SPECIES_BRELOOM] = gMonIcon_Breloom,
    [SPECIES_SPINDA] = gMonIcon_Spinda,
    [SPECIES_WINGULL] = gMonIcon_Wingull,
    [SPECIES_PELIPPER] = gMonIcon_Pelipper,
    [SPECIES_SURSKIT] = gMonIcon_Surskit,
    [SPECIES_MASQUERAIN] = gMonIcon_Masquerain,
    [SPECIES_WAILMER] = gMonIcon_Wailmer,
    [SPECIES_WAILORD] = gMonIcon_Wailord,
    [SPECIES_SKITTY] = gMonIcon_Skitty,
    [SPECIES_DELCATTY] = gMonIcon_Delcatty,
    [SPECIES_KECLEON] = gMonIcon_Kecleon,
    [SPECIES_BALTOY] = gMonIcon_Baltoy,
    [SPECIES_CLAYDOL] = gMonIcon_Claydol,
    [SPECIES_NOSEPASS] = gMonIcon_Nosepass,
    [SPECIES_TORKOAL] = gMonIcon_Torkoal,
    [SPECIES_SABLEYE] = gMonIcon_Sableye,
    [SPECIES_BARBOACH] = gMonIcon_Barboach,
    [SPECIES_WHISCASH] = gMonIcon_Whiscash,
    [SPECIES_LUVDISC] = gMonIcon_Luvdisc,
    [SPECIES_CORPHISH] = gMonIcon_Corphish,
    [SPECIES_CRAWDAUNT] = gMonIcon_Crawdaunt,
    [SPECIES_FEEBAS] = gMonIcon_Feebas,
    [SPECIES_MILOTIC] = gMonIcon_Milotic,
    [SPECIES_CARVANHA] = gMonIcon_Carvanha,
    [SPECIES_SHARPEDO] = gMonIcon_Sharpedo,
    [SPECIES_TRAPINCH] = gMonIcon_Trapinch,
    [SPECIES_VIBRAVA] = gMonIcon_Vibrava,
    [SPECIES_FLYGON] = gMonIcon_Flygon,
    [SPECIES_MAKUHITA] = gMonIcon_Makuhita,
    [SPECIES_HARIYAMA] = gMonIcon_Hariyama,
    [SPECIES_ELECTRIKE] = gMonIcon_Electrike,
    [SPECIES_MANECTRIC] = gMonIcon_Manectric,
    [SPECIES_NUMEL] = gMonIcon_Numel,
    [SPECIES_CAMERUPT] = gMonIcon_Camerupt,
    [SPECIES_SPHEAL] = gMonIcon_Spheal,
    [SPECIES_SEALEO] = gMonIcon_Sealeo,
    [SPECIES_WALREIN] = gMonIcon_Walrein,
    [SPECIES_CACNEA] = gMonIcon_Cacnea,
    [SPECIES_CACTURNE] = gMonIcon_Cacturne,
    [SPECIES_SNORUNT] = gMonIcon_Snorunt,
    [SPECIES_GLALIE] = gMonIcon_Glalie,
    [SPECIES_LUNATONE] = gMonIcon_Lunatone,
    [SPECIES_SOLROCK] = gMonIcon_Solrock,
    [SPECIES_AZURILL] = gMonIcon_Azurill,
    [SPECIES_SPOINK] = gMonIcon_Spoink,
    [SPECIES_GRUMPIG] = gMonIcon_Grumpig,
    [SPECIES_PLUSLE] = gMonIcon_Plusle,
    [SPECIES_MINUN] = gMonIcon_Minun,
    [SPECIES_MAWILE] = gMonIcon_Mawile,
    [SPECIES_MEDITITE] = gMonIcon_Meditite,
    [SPECIES_MEDICHAM] = gMonIcon_Medicham,
    [SPECIES_SWABLU] = gMonIcon_Swablu,
    [SPECIES_ALTARIA] = gMonIcon_Altaria,
    [SPECIES_WYNAUT] = gMonIcon_Wynaut,
    [SPECIES_DUSKULL] = gMonIcon_Duskull,
    [SPECIES_DUSCLOPS] = gMonIcon_Dusclops,
    [SPECIES_ROSELIA] = gMonIcon_Roselia,
    [SPECIES_SLAKOTH] = gMonIcon_Slakoth,
    [SPECIES_VIGOROTH] = gMonIcon_Vigoroth,
    [SPECIES_SLAKING] = gMonIcon_Slaking,
    [SPECIES_GULPIN] = gMonIcon_Gulpin,
    [SPECIES_SWALOT] = gMonIcon_Swalot,
    [SPECIES_TROPIUS] = gMonIcon_Tropius,
    [SPECIES_WHISMUR] = gMonIcon_Whismur,
    [SPECIES_LOUDRED] = gMonIcon_Loudred,
    [SPECIES_EXPLOUD] = gMonIcon_Exploud,
    [SPECIES_CLAMPERL] = gMonIcon_Clamperl,
    [SPECIES_HUNTAIL] = gMonIcon_Huntail,
    [SPECIES_GOREBYSS] = gMonIcon_Gorebyss,
    [SPECIES_ABSOL] = gMonIcon_Absol,
    [SPECIES_SHUPPET] = gMonIcon_Shuppet,
    [SPECIES_BANETTE] = gMonIcon_Banette,
    [SPECIES_SEVIPER] = gMonIcon_Seviper,
    [SPECIES_ZANGOOSE] = gMonIcon_Zangoose,
    [SPECIES_RELICANTH] = gMonIcon_Relicanth,
    [SPECIES_ARON] = gMonIcon_Aron,
    [SPECIES_LAIRON] = gMonIcon_Lairon,
    [SPECIES_AGGRON] = gMonIcon_Aggron,
    [SPECIES_CASTFORM_NORMAL] = gMonIcon_CastformNormal,
    [SPECIES_VOLBEAT] = gMonIcon_Volbeat,
    [SPECIES_ILLUMISE] = gMonIcon_Illumise,
    [SPECIES_LILEEP] = gMonIcon_Lileep,
    [SPECIES_CRADILY] = gMonIcon_Cradily,
    [SPECIES_ANORITH] = gMonIcon_Anorith,
    [SPECIES_ARMALDO] = gMonIcon_Armaldo,
    [SPECIES_RALTS] = gMonIcon_Ralts,
    [SPECIES_KIRLIA] = gMonIcon_Kirlia,
    [SPECIES_GARDEVOIR] = gMonIcon_Gardevoir,
    [SPECIES_BAGON] = gMonIcon_Bagon,
    [SPECIES_SHELGON] = gMonIcon_Shelgon,
    [SPECIES_SALAMENCE] = gMonIcon_Salamence,
    [SPECIES_BELDUM] = gMonIcon_Beldum,
    [SPECIES_METANG] = gMonIcon_Metang,
    [SPECIES_METAGROSS] = gMonIcon_Metagross,
    [SPECIES_REGIROCK] = gMonIcon_Regirock,
    [SPECIES_REGICE] = gMonIcon_Regice,
    [SPECIES_REGISTEEL] = gMonIcon_Registeel,
    [SPECIES_KYOGRE] = gMonIcon_Kyogre,
    [SPECIES_GROUDON] = gMonIcon_Groudon,
    [SPECIES_RAYQUAZA] = gMonIcon_Rayquaza,
    [SPECIES_LATIAS] = gMonIcon_Latias,
    [SPECIES_LATIOS] = gMonIcon_Latios,
    [SPECIES_JIRACHI] = gMonIcon_Jirachi,
    [SPECIES_DEOXYS_NORMAL] = gMonIcon_DeoxysNormal,
    [SPECIES_CHIMECHO] = gMonIcon_Chimecho,
    [SPECIES_TURTWIG] = gMonIcon_Turtwig,
    [SPECIES_GROTLE] = gMonIcon_Grotle,
    [SPECIES_TORTERRA] = gMonIcon_Torterra,
    [SPECIES_CHIMCHAR] = gMonIcon_Chimchar,
    [SPECIES_MONFERNO] = gMonIcon_Monferno,
    [SPECIES_INFERNAPE] = gMonIcon_Infernape,
    [SPECIES_PIPLUP] = gMonIcon_Piplup,
    [SPECIES_PRINPLUP] = gMonIcon_Prinplup,
    [SPECIES_EMPOLEON] = gMonIcon_Empoleon,
    [SPECIES_STARLY] = gMonIcon_Starly,
    [SPECIES_STARAVIA] = gMonIcon_Staravia,
    [SPECIES_STARAPTOR] = gMonIcon_Staraptor,
    [SPECIES_BIDOOF] = gMonIcon_Bidoof,
    [SPECIES_BIBAREL] = gMonIcon_Bibarel,
    [SPECIES_KRICKETOT] = gMonIcon_Kricketot,
    [SPECIES_KRICKETUNE] = gMonIcon_Kricketune,
    [SPECIES_SHINX] = gMonIcon_Shinx,
    [SPECIES_LUXIO] = gMonIcon_Luxio,
    [SPECIES_LUXRAY] = gMonIcon_Luxray,
    [SPECIES_BUDEW] = gMonIcon_Budew,
    [SPECIES_ROSERADE] = gMonIcon_Roserade,
    [SPECIES_CRANIDOS] = gMonIcon_Cranidos,
    [SPECIES_RAMPARDOS] = gMonIcon_Rampardos,
    [SPECIES_SHIELDON] = gMonIcon_Shieldon,
    [SPECIES_BASTIODON] = gMonIcon_Bastiodon,
    [SPECIES_BURMY_PLANT_CLOAK] = gMonIcon_BurmyPlantCloak,
    [SPECIES_WORMADAM_PLANT_CLOAK] = gMonIcon_WormadamPlantCloak,
    [SPECIES_MOTHIM] = gMonIcon_Mothim,
    [SPECIES_COMBEE] = gMonIcon_Combee,
    [SPECIES_VESPIQUEN] = gMonIcon_Vespiquen,
    [SPECIES_PACHIRISU] = gMonIcon_Pachirisu,
    [SPECIES_BUIZEL] = gMonIcon_Buizel,
    [SPECIES_FLOATZEL] = gMonIcon_Floatzel,
    [SPECIES_CHERUBI] = gMonIcon_Cherubi,
    [SPECIES_CHERRIM_OVERCAST] = gMonIcon_CherrimOvercast,
    [SPECIES_SHELLOS_WEST_SEA] = gMonIcon_ShellosWestSea,
    [SPECIES_GASTRODON_WEST_SEA] = gMonIcon_GastrodonWestSea,
    [SPECIES_AMBIPOM] = gMonIcon_Ambipom,
    [SPECIES_DRIFLOON] = gMonIcon_Drifloon,
    [SPECIES_DRIFBLIM] = gMonIcon_Drifblim,
    [SPECIES_BUNEARY] = gMonIcon_Buneary,
    [SPECIES_LOPUNNY] = gMonIcon_Lopunny,
    [SPECIES_MISMAGIUS] = gMonIcon_Mismagius,
    [SPECIES_HONCHKROW] = gMonIcon_Honchkrow,
    [SPECIES_GLAMEOW] = gMonIcon_Glameow,
    [SPECIES_PURUGLY] = gMonIcon_Purugly,
    [SPECIES_CHINGLING] = gMonIcon_Chingling,
    [SPECIES_STUNKY] = gMonIcon_Stunky,
    [SPECIES_SKUNTANK] = gMonIcon_Skuntank,
    [SPECIES_BRONZOR] = gMonIcon_Bronzor,
    [SPECIES_BRONZONG] = gMonIcon_Bronzong,
    [SPECIES_BONSLY] = gMonIcon_Bonsly,
    [SPECIES_MIME_JR] = gMonIcon_MimeJr,
    [SPECIES_HAPPINY] = gMonIcon_Happiny,
    [SPECIES_CHATOT] = gMonIcon_Chatot,
    [SPECIES_SPIRITOMB] = gMonIcon_Spiritomb,
    [SPECIES_GIBLE] = gMonIcon_Gible,
    [SPECIES_GABITE] = gMonIcon_Gabite,
    [SPECIES_GARCHOMP] = gMonIcon_Garchomp,
    [SPECIES_MUNCHLAX] = gMonIcon_Munchlax,
    [SPECIES_RIOLU] = gMonIcon_Riolu,
    [SPECIES_LUCARIO] = gMonIcon_Lucario,
    [SPECIES_HIPPOPOTAS] = gMonIcon_Hippopotas,
    [SPECIES_HIPPOWDON] = gMonIcon_Hippowdon,
    [SPECIES_SKORUPI] = gMonIcon_Skorupi,
    [SPECIES_DRAPION] = gMonIcon_Drapion,
    [SPECIES_CROAGUNK] = gMonIcon_Croagunk,
    [SPECIES_TOXICROAK] = gMonIcon_Toxicroak,
    [SPECIES_CARNIVINE] = gMonIcon_Carnivine,
    [SPECIES_FINNEON] = gMonIcon_Finneon,
    [SPECIES_LUMINEON] = gMonIcon_Lumineon,
    [SPECIES_MANTYKE] = gMonIcon_Mantyke,
    [SPECIES_SNOVER] = gMonIcon_Snover,
    [SPECIES_ABOMASNOW] = gMonIcon_Abomasnow,
    [SPECIES_WEAVILE] = gMonIcon_Weavile,
    [SPECIES_MAGNEZONE] = gMonIcon_Magnezone,
    [SPECIES_LICKILICKY] = gMonIcon_Lickilicky,
    [SPECIES_RHYPERIOR] = gMonIcon_Rhyperior,
    [SPECIES_TANGROWTH] = gMonIcon_Tangrowth,
    [SPECIES_ELECTIVIRE] = gMonIcon_Electivire,
    [SPECIES_MAGMORTAR] = gMonIcon_Magmortar,
    [SPECIES_TOGEKISS] = gMonIcon_Togekiss,
    [SPECIES_YANMEGA] = gMonIcon_Yanmega,
    [SPECIES_LEAFEON] = gMonIcon_Leafeon,
    [SPECIES_GLACEON] = gMonIcon_Glaceon,
    [SPECIES_GLISCOR] = gMonIcon_Gliscor,
    [SPECIES_MAMOSWINE] = gMonIcon_Mamoswine,
    [SPECIES_PORYGON_Z] = gMonIcon_Porygon_Z,
    [SPECIES_GALLADE] = gMonIcon_Gallade,
    [SPECIES_PROBOPASS] = gMonIcon_Probopass,
    [SPECIES_DUSKNOIR] = gMonIcon_Dusknoir,
    [SPECIES_FROSLASS] = gMonIcon_Froslass,
    [SPECIES_ROTOM] = gMonIcon_Rotom,
    [SPECIES_UXIE] = gMonIcon_Uxie,
    [SPECIES_MESPRIT] = gMonIcon_Mesprit,
    [SPECIES_AZELF] = gMonIcon_Azelf,
    [SPECIES_DIALGA] = gMonIcon_Dialga,
    [SPECIES_PALKIA] = gMonIcon_Palkia,
    [SPECIES_HEATRAN] = gMonIcon_Heatran,
    [SPECIES_REGIGIGAS] = gMonIcon_Regigigas,
    [SPECIES_GIRATINA_ALTERED] = gMonIcon_GiratinaAltered,
    [SPECIES_CRESSELIA] = gMonIcon_Cresselia,
    [SPECIES_PHIONE] = gMonIcon_Phione,
    [SPECIES_MANAPHY] = gMonIcon_Manaphy,
    [SPECIES_DARKRAI] = gMonIcon_Darkrai,
    [SPECIES_SHAYMIN_LAND] = gMonIcon_ShayminLand,
    [SPECIES_ARCEUS_NORMAL] = gMonIcon_Arceus,
    [SPECIES_VICTINI] = gMonIcon_Victini,
    [SPECIES_SNIVY] = gMonIcon_Snivy,
    [SPECIES_SERVINE] = gMonIcon_Servine,
    [SPECIES_SERPERIOR] = gMonIcon_Serperior,
    [SPECIES_TEPIG] = gMonIcon_Tepig,
    [SPECIES_PIGNITE] = gMonIcon_Pignite,
    [SPECIES_EMBOAR] = gMonIcon_Emboar,
    [SPECIES_OSHAWOTT] = gMonIcon_Oshawott,
    [SPECIES_DEWOTT] = gMonIcon_Dewott,
    [SPECIES_SAMUROTT] = gMonIcon_Samurott,
    [SPECIES_PATRAT] = gMonIcon_Patrat,
    [SPECIES_WATCHOG] = gMonIcon_Watchog,
    [SPECIES_LILLIPUP] = gMonIcon_Lillipup,
    [SPECIES_HERDIER] = gMonIcon_Herdier,
    [SPECIES_STOUTLAND] = gMonIcon_Stoutland,
    [SPECIES_PURRLOIN] = gMonIcon_Purrloin,
    [SPECIES_LIEPARD] = gMonIcon_Liepard,
    [SPECIES_PANSAGE] = gMonIcon_Pansage,
    [SPECIES_SIMISAGE] = gMonIcon_Simisage,
    [SPECIES_PANSEAR] = gMonIcon_Pansear,
    [SPECIES_SIMISEAR] = gMonIcon_Simisear,
    [SPECIES_PANPOUR] = gMonIcon_Panpour,
    [SPECIES_SIMIPOUR] = gMonIcon_Simipour,
    [SPECIES_MUNNA] = gMonIcon_Munna,
    [SPECIES_MUSHARNA] = gMonIcon_Musharna,
    [SPECIES_PIDOVE] = gMonIcon_Pidove,
    [SPECIES_TRANQUILL] = gMonIcon_Tranquill,
    [SPECIES_UNFEZANT] = gMonIcon_Unfezant,
    [SPECIES_BLITZLE] = gMonIcon_Blitzle,
    [SPECIES_ZEBSTRIKA] = gMonIcon_Zebstrika,
    [SPECIES_ROGGENROLA] = gMonIcon_Roggenrola,
    [SPECIES_BOLDORE] = gMonIcon_Boldore,
    [SPECIES_GIGALITH] = gMonIcon_Gigalith,
    [SPECIES_WOOBAT] = gMonIcon_Woobat,
    [SPECIES_SWOOBAT] = gMonIcon_Swoobat,
    [SPECIES_DRILBUR] = gMonIcon_Drilbur,
    [SPECIES_EXCADRILL] = gMonIcon_Excadrill,
    [SPECIES_AUDINO] = gMonIcon_Audino,
    [SPECIES_TIMBURR] = gMonIcon_Timburr,
    [SPECIES_GURDURR] = gMonIcon_Gurdurr,
    [SPECIES_CONKELDURR] = gMonIcon_Conkeldurr,
    [SPECIES_TYMPOLE] = gMonIcon_Tympole,
    [SPECIES_PALPITOAD] = gMonIcon_Palpitoad,
    [SPECIES_SEISMITOAD] = gMonIcon_Seismitoad,
    [SPECIES_THROH] = gMonIcon_Throh,
    [SPECIES_SAWK] = gMonIcon_Sawk,
    [SPECIES_SEWADDLE] = gMonIcon_Sewaddle,
    [SPECIES_SWADLOON] = gMonIcon_Swadloon,
    [SPECIES_LEAVANNY] = gMonIcon_Leavanny,
    [SPECIES_VENIPEDE] = gMonIcon_Venipede,
    [SPECIES_WHIRLIPEDE] = gMonIcon_Whirlipede,
    [SPECIES_SCOLIPEDE] = gMonIcon_Scolipede,
    [SPECIES_COTTONEE] = gMonIcon_Cottonee,
    [SPECIES_WHIMSICOTT] = gMonIcon_Whimsicott,
    [SPECIES_PETILIL] = gMonIcon_Petilil,
    [SPECIES_LILLIGANT] = gMonIcon_Lilligant,
    [SPECIES_BASCULIN_RED_STRIPED] = gMonIcon_BasculinRedStriped,
    [SPECIES_SANDILE] = gMonIcon_Sandile,
    [SPECIES_KROKOROK] = gMonIcon_Krokorok,
    [SPECIES_KROOKODILE] = gMonIcon_Krookodile,
    [SPECIES_DARUMAKA] = gMonIcon_Darumaka,
    [SPECIES_DARMANITAN_STANDARD_MODE] = gMonIcon_DarmanitanStandardMode,
    [SPECIES_MARACTUS] = gMonIcon_Maractus,
    [SPECIES_DWEBBLE] = gMonIcon_Dwebble,
    [SPECIES_CRUSTLE] = gMonIcon_Crustle,
    [SPECIES_SCRAGGY] = gMonIcon_Scraggy,
    [SPECIES_SCRAFTY] = gMonIcon_Scrafty,
    [SPECIES_SIGILYPH] = gMonIcon_Sigilyph,
    [SPECIES_YAMASK] = gMonIcon_Yamask,
    [SPECIES_COFAGRIGUS] = gMonIcon_Cofagrigus,
    [SPECIES_TIRTOUGA] = gMonIcon_Tirtouga,
    [SPECIES_CARRACOSTA] = gMonIcon_Carracosta,
    [SPECIES_ARCHEN] = gMonIcon_Archen,
    [SPECIES_ARCHEOPS] = gMonIcon_Archeops,
    [SPECIES_TRUBBISH] = gMonIcon_Trubbish,
    [SPECIES_GARBODOR] = gMonIcon_Garbodor,
    [SPECIES_ZORUA] = gMonIcon_Zorua,
    [SPECIES_ZOROARK] = gMonIcon_Zoroark,
    [SPECIES_MINCCINO] = gMonIcon_Minccino,
    [SPECIES_CINCCINO] = gMonIcon_Cinccino,
    [SPECIES_GOTHITA] = gMonIcon_Gothita,
    [SPECIES_GOTHORITA] = gMonIcon_Gothorita,
    [SPECIES_GOTHITELLE] = gMonIcon_Gothitelle,
    [SPECIES_SOLOSIS] = gMonIcon_Solosis,
    [SPECIES_DUOSION] = gMonIcon_Duosion,
    [SPECIES_REUNICLUS] = gMonIcon_Reuniclus,
    [SPECIES_DUCKLETT] = gMonIcon_Ducklett,
    [SPECIES_SWANNA] = gMonIcon_Swanna,
    [SPECIES_VANILLITE] = gMonIcon_Vanillite,
    [SPECIES_VANILLISH] = gMonIcon_Vanillish,
    [SPECIES_VANILLUXE] = gMonIcon_Vanilluxe,
    [SPECIES_DEERLING_SPRING] = gMonIcon_DeerlingSpring,
    [SPECIES_SAWSBUCK_SPRING] = gMonIcon_SawsbuckSpring,
    [SPECIES_EMOLGA] = gMonIcon_Emolga,
    [SPECIES_KARRABLAST] = gMonIcon_Karrablast,
    [SPECIES_ESCAVALIER] = gMonIcon_Escavalier,
    [SPECIES_FOONGUS] = gMonIcon_Foongus,
    [SPECIES_AMOONGUSS] = gMonIcon_Amoonguss,
    [SPECIES_FRILLISH] = gMonIcon_Frillish,
    [SPECIES_JELLICENT] = gMonIcon_Jellicent,
    [SPECIES_ALOMOMOLA] = gMonIcon_Alomomola,
    [SPECIES_JOLTIK] = gMonIcon_Joltik,
    [SPECIES_GALVANTULA] = gMonIcon_Galvantula,
    [SPECIES_FERROSEED] = gMonIcon_Ferroseed,
    [SPECIES_FERROTHORN] = gMonIcon_Ferrothorn,
    [SPECIES_KLINK] = gMonIcon_Klink,
    [SPECIES_KLANG] = gMonIcon_Klang,
    [SPECIES_KLINKLANG] = gMonIcon_Klinklang,
    [SPECIES_TYNAMO] = gMonIcon_Tynamo,
    [SPECIES_EELEKTRIK] = gMonIcon_Eelektrik,
    [SPECIES_EELEKTROSS] = gMonIcon_Eelektross,
    [SPECIES_ELGYEM] = gMonIcon_Elgyem,
    [SPECIES_BEHEEYEM] = gMonIcon_Beheeyem,
    [SPECIES_LITWICK] = gMonIcon_Litwick,
    [SPECIES_LAMPENT] = gMonIcon_Lampent,
    [SPECIES_CHANDELURE] = gMonIcon_Chandelure,
    [SPECIES_AXEW] = gMonIcon_Axew,
    [SPECIES_FRAXURE] = gMonIcon_Fraxure,
    [SPECIES_HAXORUS] = gMonIcon_Haxorus,
    [SPECIES_CUBCHOO] = gMonIcon_Cubchoo,
    [SPECIES_BEARTIC] = gMonIcon_Beartic,
    [SPECIES_CRYOGONAL] = gMonIcon_Cryogonal,
    [SPECIES_SHELMET] = gMonIcon_Shelmet,
    [SPECIES_ACCELGOR] = gMonIcon_Accelgor,
    [SPECIES_STUNFISK] = gMonIcon_Stunfisk,
    [SPECIES_MIENFOO] = gMonIcon_Mienfoo,
    [SPECIES_MIENSHAO] = gMonIcon_Mienshao,
    [SPECIES_DRUDDIGON] = gMonIcon_Druddigon,
    [SPECIES_GOLETT] = gMonIcon_Golett,
    [SPECIES_GOLURK] = gMonIcon_Golurk,
    [SPECIES_PAWNIARD] = gMonIcon_Pawniard,
    [SPECIES_BISHARP] = gMonIcon_Bisharp,
    [SPECIES_BOUFFALANT] = gMonIcon_Bouffalant,
    [SPECIES_RUFFLET] = gMonIcon_Rufflet,
    [SPECIES_BRAVIARY] = gMonIcon_Braviary,
    [SPECIES_VULLABY] = gMonIcon_Vullaby,
    [SPECIES_MANDIBUZZ] = gMonIcon_Mandibuzz,
    [SPECIES_HEATMOR] = gMonIcon_Heatmor,
    [SPECIES_DURANT] = gMonIcon_Durant,
    [SPECIES_DEINO] = gMonIcon_Deino,
    [SPECIES_ZWEILOUS] = gMonIcon_Zweilous,
    [SPECIES_HYDREIGON] = gMonIcon_Hydreigon,
    [SPECIES_LARVESTA] = gMonIcon_Larvesta,
    [SPECIES_VOLCARONA] = gMonIcon_Volcarona,
    [SPECIES_COBALION] = gMonIcon_Cobalion,
    [SPECIES_TERRAKION] = gMonIcon_Terrakion,
    [SPECIES_VIRIZION] = gMonIcon_Virizion,
    [SPECIES_TORNADUS_INCARNATE] = gMonIcon_TornadusIncarnate,
    [SPECIES_THUNDURUS_INCARNATE] = gMonIcon_ThundurusIncarnate,
    [SPECIES_RESHIRAM] = gMonIcon_Reshiram,
    [SPECIES_ZEKROM] = gMonIcon_Zekrom,
    [SPECIES_LANDORUS_INCARNATE] = gMonIcon_LandorusIncarnate,
    [SPECIES_KYUREM] = gMonIcon_Kyurem,
    [SPECIES_KELDEO_ORDINARY] = gMonIcon_KeldeoOrdinary,
    [SPECIES_MELOETTA_ARIA] = gMonIcon_MeloettaAria,
    [SPECIES_GENESECT] = gMonIcon_Genesect,
    [SPECIES_CHESPIN] = gMonIcon_Chespin,
    [SPECIES_QUILLADIN] = gMonIcon_Quilladin,
    [SPECIES_CHESNAUGHT] = gMonIcon_Chesnaught,
    [SPECIES_FENNEKIN] = gMonIcon_Fennekin,
    [SPECIES_BRAIXEN] = gMonIcon_Braixen,
    [SPECIES_DELPHOX] = gMonIcon_Delphox,
    [SPECIES_FROAKIE] = gMonIcon_Froakie,
    [SPECIES_FROGADIER] = gMonIcon_Frogadier,
    [SPECIES_GRENINJA] = gMonIcon_Greninja,
    [SPECIES_BUNNELBY] = gMonIcon_Bunnelby,
    [SPECIES_DIGGERSBY] = gMonIcon_Diggersby,
    [SPECIES_FLETCHLING] = gMonIcon_Fletchling,
    [SPECIES_FLETCHINDER] = gMonIcon_Fletchinder,
    [SPECIES_TALONFLAME] = gMonIcon_Talonflame,
    [SPECIES_SCATTERBUG] = gMonIcon_Scatterbug,
    [SPECIES_SPEWPA] = gMonIcon_Spewpa,
    [SPECIES_VIVILLON_ICY_SNOW] = gMonIcon_VivillonIcySnow,
    [SPECIES_LITLEO] = gMonIcon_Litleo,
    [SPECIES_PYROAR] = gMonIcon_Pyroar,
    [SPECIES_FLABEBE_RED_FLOWER] = gMonIcon_FlabebeRedFlower,
    [SPECIES_FLOETTE_RED_FLOWER] = gMonIcon_FloetteRedFlower,
    [SPECIES_FLORGES_RED_FLOWER] = gMonIcon_FlorgesRedFlower,
    [SPECIES_SKIDDO] = gMonIcon_Skiddo,
    [SPECIES_GOGOAT] = gMonIcon_Gogoat,
    [SPECIES_PANCHAM] = gMonIcon_Pancham,
    [SPECIES_PANGORO] = gMonIcon_Pangoro,
    [SPECIES_FURFROU_NATURAL] = gMonIcon_FurfrouNatural,
    [SPECIES_ESPURR] = gMonIcon_Espurr,
    [SPECIES_MEOWSTIC_MALE] = gMonIcon_MeowsticMale,
    [SPECIES_HONEDGE] = gMonIcon_Honedge,
    [SPECIES_DOUBLADE] = gMonIcon_Doublade,
    [SPECIES_AEGISLASH_SHIELD] = gMonIcon_AegislashShield,
    [SPECIES_SPRITZEE] = gMonIcon_Spritzee,
    [SPECIES_AROMATISSE] = gMonIcon_Aromatisse,
    [SPECIES_SWIRLIX] = gMonIcon_Swirlix,
    [SPECIES_SLURPUFF] = gMonIcon_Slurpuff,
    [SPECIES_INKAY] = gMonIcon_Inkay,
    [SPECIES_MALAMAR] = gMonIcon_Malamar,
    [SPECIES_BINACLE] = gMonIcon_Binacle,
    [SPECIES_BARBARACLE] = gMonIcon_Barbaracle,
    [SPECIES_SKRELP] = gMonIcon_Skrelp,
    [SPECIES_DRAGALGE] = gMonIcon_Dragalge,
    [SPECIES_CLAUNCHER] = gMonIcon_Clauncher,
    [SPECIES_CLAWITZER] = gMonIcon_Clawitzer,
    [SPECIES_HELIOPTILE] = gMonIcon_Helioptile,
    [SPECIES_HELIOLISK] = gMonIcon_Heliolisk,
    [SPECIES_TYRUNT] = gMonIcon_Tyrunt,
    [SPECIES_TYRANTRUM] = gMonIcon_Tyrantrum,
    [SPECIES_AMAURA] = gMonIcon_Amaura,
    [SPECIES_AURORUS] = gMonIcon_Aurorus,
    [SPECIES_SYLVEON] = gMonIcon_Sylveon,
    [SPECIES_HAWLUCHA] = gMonIcon_Hawlucha,
    [SPECIES_DEDENNE] = gMonIcon_Dedenne,
    [SPECIES_CARBINK] = gMonIcon_Carbink,
    [SPECIES_GOOMY] = gMonIcon_Goomy,
    [SPECIES_SLIGGOO] = gMonIcon_Sliggoo,
    [SPECIES_GOODRA] = gMonIcon_Goodra,
    [SPECIES_KLEFKI] = gMonIcon_Klefki,
    [SPECIES_PHANTUMP] = gMonIcon_Phantump,
    [SPECIES_TREVENANT] = gMonIcon_Trevenant,
    [SPECIES_PUMPKABOO_AVERAGE] = gMonIcon_Pumpkaboo,
    [SPECIES_GOURGEIST_AVERAGE] = gMonIcon_Gourgeist,
    [SPECIES_BERGMITE] = gMonIcon_Bergmite,
    [SPECIES_AVALUGG] = gMonIcon_Avalugg,
    [SPECIES_NOIBAT] = gMonIcon_Noibat,
    [SPECIES_NOIVERN] = gMonIcon_Noivern,
    [SPECIES_XERNEAS_NEUTRAL] = gMonIcon_XerneasNeutral,
    [SPECIES_YVELTAL] = gMonIcon_Yveltal,
    [SPECIES_ZYGARDE_50_AURA_BREAK] = gMonIcon_Zygarde50,
    [SPECIES_DIANCIE] = gMonIcon_Diancie,
    [SPECIES_HOOPA_CONFINED] = gMonIcon_HoopaConfined,
    [SPECIES_VOLCANION] = gMonIcon_Volcanion,
    [SPECIES_ROWLET] = gMonIcon_Rowlet,
    [SPECIES_DARTRIX] = gMonIcon_Dartrix,
    [SPECIES_DECIDUEYE] = gMonIcon_Decidueye,
    [SPECIES_LITTEN] = gMonIcon_Litten,
    [SPECIES_TORRACAT] = gMonIcon_Torracat,
    [SPECIES_INCINEROAR] = gMonIcon_Incineroar,
    [SPECIES_POPPLIO] = gMonIcon_Popplio,
    [SPECIES_BRIONNE] = gMonIcon_Brionne,
    [SPECIES_PRIMARINA] = gMonIcon_Primarina,
    [SPECIES_PIKIPEK] = gMonIcon_Pikipek,
    [SPECIES_TRUMBEAK] = gMonIcon_Trumbeak,
    [SPECIES_TOUCANNON] = gMonIcon_Toucannon,
    [SPECIES_YUNGOOS] = gMonIcon_Yungoos,
    [SPECIES_GUMSHOOS] = gMonIcon_Gumshoos,
    [SPECIES_GRUBBIN] = gMonIcon_Grubbin,
    [SPECIES_CHARJABUG] = gMonIcon_Charjabug,
    [SPECIES_VIKAVOLT] = gMonIcon_Vikavolt,
    [SPECIES_CRABRAWLER] = gMonIcon_Crabrawler,
    [SPECIES_CRABOMINABLE] = gMonIcon_Crabominable,
    [SPECIES_ORICORIO_BAILE] = gMonIcon_OricorioBaile,
    [SPECIES_CUTIEFLY] = gMonIcon_Cutiefly,
    [SPECIES_RIBOMBEE] = gMonIcon_Ribombee,
    [SPECIES_ROCKRUFF] = gMonIcon_Rockruff,
    [SPECIES_LYCANROC_MIDDAY] = gMonIcon_LycanrocMidday,
    [SPECIES_WISHIWASHI_SOLO] = gMonIcon_WishiwashiSolo,
    [SPECIES_MAREANIE] = gMonIcon_Mareanie,
    [SPECIES_TOXAPEX] = gMonIcon_Toxapex,
    [SPECIES_MUDBRAY] = gMonIcon_Mudbray,
    [SPECIES_MUDSDALE] = gMonIcon_Mudsdale,
    [SPECIES_DEWPIDER] = gMonIcon_Dewpider,
    [SPECIES_ARAQUANID] = gMonIcon_Araquanid,
    [SPECIES_FOMANTIS] = gMonIcon_Fomantis,
    [SPECIES_LURANTIS] = gMonIcon_Lurantis,
    [SPECIES_MORELULL] = gMonIcon_Morelull,
    [SPECIES_SHIINOTIC] = gMonIcon_Shiinotic,
    [SPECIES_SALANDIT] = gMonIcon_Salandit,
    [SPECIES_SALAZZLE] = gMonIcon_Salazzle,
    [SPECIES_STUFFUL] = gMonIcon_Stufful,
    [SPECIES_BEWEAR] = gMonIcon_Bewear,
    [SPECIES_BOUNSWEET] = gMonIcon_Bounsweet,
    [SPECIES_STEENEE] = gMonIcon_Steenee,
    [SPECIES_TSAREENA] = gMonIcon_Tsareena,
    [SPECIES_COMFEY] = gMonIcon_Comfey,
    [SPECIES_ORANGURU] = gMonIcon_Oranguru,
    [SPECIES_PASSIMIAN] = gMonIcon_Passimian,
    [SPECIES_WIMPOD] = gMonIcon_Wimpod,
    [SPECIES_GOLISOPOD] = gMonIcon_Golisopod,
    [SPECIES_SANDYGAST] = gMonIcon_Sandygast,
    [SPECIES_PALOSSAND] = gMonIcon_Palossand,
    [SPECIES_PYUKUMUKU] = gMonIcon_Pyukumuku,
    [SPECIES_TYPE_NULL] = gMonIcon_TypeNull,
    [SPECIES_SILVALLY_NORMAL] = gMonIcon_Silvally,
    [SPECIES_MINIOR_METEOR_RED] = gMonIcon_MiniorMeteor,
    [SPECIES_KOMALA] = gMonIcon_Komala,
    [SPECIES_TURTONATOR] = gMonIcon_Turtonator,
    [SPECIES_TOGEDEMARU] = gMonIcon_Togedemaru,
    [SPECIES_MIMIKYU_DISGUISED] = gMonIcon_MimikyuDisguised,
    [SPECIES_BRUXISH] = gMonIcon_Bruxish,
    [SPECIES_DRAMPA] = gMonIcon_Drampa,
    [SPECIES_DHELMISE] = gMonIcon_Dhelmise,
    [SPECIES_JANGMO_O] = gMonIcon_JangmoO,
    [SPECIES_HAKAMO_O] = gMonIcon_HakamoO,
    [SPECIES_KOMMO_O] = gMonIcon_KommoO,
    [SPECIES_TAPU_KOKO] = gMonIcon_TapuKoko,
    [SPECIES_TAPU_LELE] = gMonIcon_TapuLele,
    [SPECIES_TAPU_BULU] = gMonIcon_TapuBulu,
    [SPECIES_TAPU_FINI] = gMonIcon_TapuFini,
    [SPECIES_COSMOG] = gMonIcon_Cosmog,
    [SPECIES_COSMOEM] = gMonIcon_Cosmoem,
    [SPECIES_SOLGALEO] = gMonIcon_Solgaleo,
    [SPECIES_LUNALA] = gMonIcon_Lunala,
    [SPECIES_NIHILEGO] = gMonIcon_Nihilego,
    [SPECIES_BUZZWOLE] = gMonIcon_Buzzwole,
    [SPECIES_PHEROMOSA] = gMonIcon_Pheromosa,
    [SPECIES_XURKITREE] = gMonIcon_Xurkitree,
    [SPECIES_CELESTEELA] = gMonIcon_Celesteela,
    [SPECIES_KARTANA] = gMonIcon_Kartana,
    [SPECIES_GUZZLORD] = gMonIcon_Guzzlord,
    [SPECIES_NECROZMA] = gMonIcon_Necrozma,
    [SPECIES_MAGEARNA] = gMonIcon_Magearna,
    [SPECIES_MARSHADOW] = gMonIcon_Marshadow,
    [SPECIES_POIPOLE] = gMonIcon_Poipole,
    [SPECIES_NAGANADEL] = gMonIcon_Naganadel,
    [SPECIES_STAKATAKA] = gMonIcon_Stakataka,
    [SPECIES_BLACEPHALON] = gMonIcon_Blacephalon,
    [SPECIES_ZERAORA] = gMonIcon_Zeraora,
    [SPECIES_MELTAN] = gMonIcon_Meltan,
    [SPECIES_MELMETAL] = gMonIcon_Melmetal,
    [SPECIES_GROOKEY] = gMonIcon_Grookey,
    [SPECIES_THWACKEY] = gMonIcon_Thwackey,
    [SPECIES_RILLABOOM] = gMonIcon_Rillaboom,
    [SPECIES_SCORBUNNY] = gMonIcon_Scorbunny,
    [SPECIES_RABOOT] = gMonIcon_Raboot,
    [SPECIES_CINDERACE] = gMonIcon_Cinderace,
    [SPECIES_SOBBLE] = gMonIcon_Sobble,
    [SPECIES_DRIZZILE] = gMonIcon_Drizzile,
    [SPECIES_INTELEON] = gMonIcon_Inteleon,
    [SPECIES_SKWOVET] = gMonIcon_Skwovet,
    [SPECIES_GREEDENT] = gMonIcon_Greedent,
    [SPECIES_ROOKIDEE] = gMonIcon_Rookidee,
    [SPECIES_CORVISQUIRE] = gMonIcon_Corvisquire,
    [SPECIES_CORVIKNIGHT] = gMonIcon_Corviknight,
    [SPECIES_BLIPBUG] = gMonIcon_Blipbug,
    [SPECIES_DOTTLER] = gMonIcon_Dottler,
    [SPECIES_ORBEETLE] = gMonIcon_Orbeetle,
    [SPECIES_NICKIT] = gMonIcon_Nickit,
    [SPECIES_THIEVUL] = gMonIcon_Thievul,
    [SPECIES_GOSSIFLEUR] = gMonIcon_Gossifleur,
    [SPECIES_ELDEGOSS] = gMonIcon_Eldegoss,
    [SPECIES_WOOLOO] = gMonIcon_Wooloo,
    [SPECIES_DUBWOOL] = gMonIcon_Dubwool,
    [SPECIES_CHEWTLE] = gMonIcon_Chewtle,
    [SPECIES_DREDNAW] = gMonIcon_Drednaw,
    [SPECIES_YAMPER] = gMonIcon_Yamper,
    [SPECIES_BOLTUND] = gMonIcon_Boltund,
    [SPECIES_ROLYCOLY] = gMonIcon_Rolycoly,
    [SPECIES_CARKOL] = gMonIcon_Carkol,
    [SPECIES_COALOSSAL] = gMonIcon_Coalossal,
    [SPECIES_APPLIN] = gMonIcon_Applin,
    [SPECIES_FLAPPLE] = gMonIcon_Flapple,
    [SPECIES_APPLETUN] = gMonIcon_Appletun,
    [SPECIES_SILICOBRA] = gMonIcon_Silicobra,
    [SPECIES_SANDACONDA] = gMonIcon_Sandaconda,
    [SPECIES_CRAMORANT] = gMonIcon_Cramorant,
    [SPECIES_ARROKUDA] = gMonIcon_Arrokuda,
    [SPECIES_BARRASKEWDA] = gMonIcon_Barraskewda,
    [SPECIES_TOXEL] = gMonIcon_Toxel,
    [SPECIES_TOXTRICITY_AMPED] = gMonIcon_ToxtricityAmped,
    [SPECIES_SIZZLIPEDE] = gMonIcon_Sizzlipede,
    [SPECIES_CENTISKORCH] = gMonIcon_Centiskorch,
    [SPECIES_CLOBBOPUS] = gMonIcon_Clobbopus,
    [SPECIES_GRAPPLOCT] = gMonIcon_Grapploct,
    [SPECIES_SINISTEA_PHONY] = gMonIcon_Sinistea,
    [SPECIES_POLTEAGEIST_PHONY] = gMonIcon_Polteageist,
    [SPECIES_HATENNA] = gMonIcon_Hatenna,
    [SPECIES_HATTREM] = gMonIcon_Hattrem,
    [SPECIES_HATTERENE] = gMonIcon_Hatterene,
    [SPECIES_IMPIDIMP] = gMonIcon_Impidimp,
    [SPECIES_MORGREM] = gMonIcon_Morgrem,
    [SPECIES_GRIMMSNARL] = gMonIcon_Grimmsnarl,
    [SPECIES_OBSTAGOON] = gMonIcon_Obstagoon,
    [SPECIES_PERRSERKER] = gMonIcon_Perrserker,
    [SPECIES_CURSOLA] = gMonIcon_Cursola,
    [SPECIES_SIRFETCHD] = gMonIcon_Sirfetchd,
    [SPECIES_MR_RIME] = gMonIcon_MrRime,
    [SPECIES_RUNERIGUS] = gMonIcon_Runerigus,
    [SPECIES_MILCERY] = gMonIcon_Milcery,
    [SPECIES_ALCREMIE_STRAWBERRY_VANILLA_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,
    [SPECIES_ALCREMIE_STRAWBERRY_RUBY_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRubyCream,
    [SPECIES_ALCREMIE_STRAWBERRY_MATCHA_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryMatchaCream,
    [SPECIES_ALCREMIE_STRAWBERRY_MINT_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryMintCream,
    [SPECIES_ALCREMIE_STRAWBERRY_LEMON_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryLemonCream,
    [SPECIES_ALCREMIE_STRAWBERRY_SALTED_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberrySaltedCream,
    [SPECIES_ALCREMIE_STRAWBERRY_RUBY_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRubySwirl,
    [SPECIES_ALCREMIE_STRAWBERRY_CARAMEL_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryCaramelSwirl,
    [SPECIES_ALCREMIE_STRAWBERRY_RAINBOW_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRainbowSwirl,
    [SPECIES_ALCREMIE_BERRY_VANILLA_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,
    [SPECIES_ALCREMIE_BERRY_RUBY_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRubyCream,
    [SPECIES_ALCREMIE_BERRY_MATCHA_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryMatchaCream,
    [SPECIES_ALCREMIE_BERRY_MINT_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryMintCream,
    [SPECIES_ALCREMIE_BERRY_LEMON_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryLemonCream,
    [SPECIES_ALCREMIE_BERRY_SALTED_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberrySaltedCream,
    [SPECIES_ALCREMIE_BERRY_RUBY_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRubySwirl,
    [SPECIES_ALCREMIE_BERRY_CARAMEL_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryCaramelSwirl,
    [SPECIES_ALCREMIE_BERRY_RAINBOW_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRainbowSwirl,
    [SPECIES_ALCREMIE_LOVE_VANILLA_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,
    [SPECIES_ALCREMIE_LOVE_RUBY_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRubyCream,
    [SPECIES_ALCREMIE_LOVE_MATCHA_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryMatchaCream,
    [SPECIES_ALCREMIE_LOVE_MINT_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryMintCream,
    [SPECIES_ALCREMIE_LOVE_LEMON_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryLemonCream,
    [SPECIES_ALCREMIE_LOVE_SALTED_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberrySaltedCream,
    [SPECIES_ALCREMIE_LOVE_RUBY_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRubySwirl,
    [SPECIES_ALCREMIE_LOVE_CARAMEL_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryCaramelSwirl,
    [SPECIES_ALCREMIE_LOVE_RAINBOW_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRainbowSwirl,
    [SPECIES_ALCREMIE_STAR_VANILLA_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,
    [SPECIES_ALCREMIE_STAR_RUBY_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRubyCream,
    [SPECIES_ALCREMIE_STAR_MATCHA_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryMatchaCream,
    [SPECIES_ALCREMIE_STAR_MINT_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryMintCream,
    [SPECIES_ALCREMIE_STAR_LEMON_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryLemonCream,
    [SPECIES_ALCREMIE_STAR_SALTED_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberrySaltedCream,
    [SPECIES_ALCREMIE_STAR_RUBY_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRubySwirl,
    [SPECIES_ALCREMIE_STAR_CARAMEL_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryCaramelSwirl,
    [SPECIES_ALCREMIE_STAR_RAINBOW_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRainbowSwirl,
    [SPECIES_ALCREMIE_CLOVER_VANILLA_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,
    [SPECIES_ALCREMIE_CLOVER_RUBY_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRubyCream,
    [SPECIES_ALCREMIE_CLOVER_MATCHA_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryMatchaCream,
    [SPECIES_ALCREMIE_CLOVER_MINT_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryMintCream,
    [SPECIES_ALCREMIE_CLOVER_LEMON_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryLemonCream,
    [SPECIES_ALCREMIE_CLOVER_SALTED_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberrySaltedCream,
    [SPECIES_ALCREMIE_CLOVER_RUBY_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRubySwirl,
    [SPECIES_ALCREMIE_CLOVER_CARAMEL_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryCaramelSwirl,
    [SPECIES_ALCREMIE_CLOVER_RAINBOW_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRainbowSwirl,
    [SPECIES_ALCREMIE_FLOWER_VANILLA_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,
    [SPECIES_ALCREMIE_FLOWER_RUBY_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRubyCream,
    [SPECIES_ALCREMIE_FLOWER_MATCHA_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryMatchaCream,
    [SPECIES_ALCREMIE_FLOWER_MINT_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryMintCream,
    [SPECIES_ALCREMIE_FLOWER_LEMON_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryLemonCream,
    [SPECIES_ALCREMIE_FLOWER_SALTED_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberrySaltedCream,
    [SPECIES_ALCREMIE_FLOWER_RUBY_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRubySwirl,
    [SPECIES_ALCREMIE_FLOWER_CARAMEL_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryCaramelSwirl,
    [SPECIES_ALCREMIE_FLOWER_RAINBOW_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRainbowSwirl,
    [SPECIES_ALCREMIE_RIBBON_VANILLA_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,
    [SPECIES_ALCREMIE_RIBBON_RUBY_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRubyCream,
    [SPECIES_ALCREMIE_RIBBON_MATCHA_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryMatchaCream,
    [SPECIES_ALCREMIE_RIBBON_MINT_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryMintCream,
    [SPECIES_ALCREMIE_RIBBON_LEMON_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryLemonCream,
    [SPECIES_ALCREMIE_RIBBON_SALTED_CREAM] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberrySaltedCream,
    [SPECIES_ALCREMIE_RIBBON_RUBY_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRubySwirl,
    [SPECIES_ALCREMIE_RIBBON_CARAMEL_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryCaramelSwirl,
    [SPECIES_ALCREMIE_RIBBON_RAINBOW_SWIRL] = gMonIcon_AlcremieStrawberryVanillaCream,//gMonIcon_AlcremieStrawberryRainbowSwirl,
    [SPECIES_FALINKS] = gMonIcon_Falinks,
    [SPECIES_PINCURCHIN] = gMonIcon_Pincurchin,
    [SPECIES_SNOM] = gMonIcon_Snom,
    [SPECIES_FROSMOTH] = gMonIcon_Frosmoth,
    [SPECIES_STONJOURNER] = gMonIcon_Stonjourner,
    [SPECIES_EISCUE_ICE_FACE] = gMonIcon_EiscueIceFace,
    [SPECIES_INDEEDEE_MALE] = gMonIcon_IndeedeeMale,
    [SPECIES_MORPEKO_FULL_BELLY] = gMonIcon_MorpekoFullBelly,
    [SPECIES_CUFANT] = gMonIcon_Cufant,
    [SPECIES_COPPERAJAH] = gMonIcon_Copperajah,
    [SPECIES_DRACOZOLT] = gMonIcon_Dracozolt,
    [SPECIES_ARCTOZOLT] = gMonIcon_Arctozolt,
    [SPECIES_DRACOVISH] = gMonIcon_Dracovish,
    [SPECIES_ARCTOVISH] = gMonIcon_Arctovish,
    [SPECIES_DURALUDON] = gMonIcon_Duraludon,
    [SPECIES_DREEPY] = gMonIcon_Dreepy,
    [SPECIES_DRAKLOAK] = gMonIcon_Drakloak,
    [SPECIES_DRAGAPULT] = gMonIcon_Dragapult,
    [SPECIES_ZACIAN_HERO_OF_MANY_BATTLES] = gMonIcon_ZacianHeroOfManyBattles,
    [SPECIES_ZAMAZENTA_HERO_OF_MANY_BATTLES] = gMonIcon_ZamazentaHeroOfManyBattles,
    [SPECIES_ETERNATUS] = gMonIcon_Eternatus,
    [SPECIES_KUBFU] = gMonIcon_Kubfu,
    [SPECIES_URSHIFU_SINGLE_STRIKE_STYLE] = gMonIcon_UrshifuSingleStrikeStyle,
    [SPECIES_ZARUDE] = gMonIcon_Zarude,
    [SPECIES_REGIELEKI] = gMonIcon_Regieleki,
    [SPECIES_REGIDRAGO] = gMonIcon_Regidrago,
    [SPECIES_GLASTRIER] = gMonIcon_Glastrier,
    [SPECIES_SPECTRIER] = gMonIcon_Spectrier,
    [SPECIES_CALYREX] = gMonIcon_Calyrex,
    [SPECIES_WYRDEER] = gMonIcon_Wyrdeer,
    [SPECIES_KLEAVOR] = gMonIcon_Kleavor,
    [SPECIES_URSALUNA] = gMonIcon_Ursaluna,
    [SPECIES_URSALUNA_BLOODMOON] = gMonIcon_UrsalunaBloodmoon,
    [SPECIES_BASCULEGION_MALE] = gMonIcon_BasculegionMale,
    [SPECIES_SNEASLER] = gMonIcon_Sneasler,
    [SPECIES_OVERQWIL] = gMonIcon_Overqwil,
    [SPECIES_ENAMORUS_INCARNATE] = gMonIcon_EnamorusIncarnate,
    [SPECIES_VENUSAUR_MEGA] = gMonIcon_VenusaurMega,
    [SPECIES_CHARIZARD_MEGA_X] = gMonIcon_CharizardMegaX,
    [SPECIES_CHARIZARD_MEGA_Y] = gMonIcon_CharizardMegaY,
    [SPECIES_BLASTOISE_MEGA] = gMonIcon_BlastoiseMega,
    [SPECIES_BEEDRILL_MEGA] = gMonIcon_BeedrillMega,
    [SPECIES_PIDGEOT_MEGA] = gMonIcon_PidgeotMega,
    [SPECIES_ALAKAZAM_MEGA] = gMonIcon_AlakazamMega,
    [SPECIES_SLOWBRO_MEGA] = gMonIcon_SlowbroMega,
    [SPECIES_GENGAR_MEGA] = gMonIcon_GengarMega,
    [SPECIES_KANGASKHAN_MEGA] = gMonIcon_KangaskhanMega,
    [SPECIES_PINSIR_MEGA] = gMonIcon_PinsirMega,
    [SPECIES_GYARADOS_MEGA] = gMonIcon_GyaradosMega,
    [SPECIES_AERODACTYL_MEGA] = gMonIcon_AerodactylMega,
    [SPECIES_MEWTWO_MEGA_X] = gMonIcon_MewtwoMegaX,
    [SPECIES_MEWTWO_MEGA_Y] = gMonIcon_MewtwoMegaY,
    [SPECIES_AMPHAROS_MEGA] = gMonIcon_AmpharosMega,
    [SPECIES_STEELIX_MEGA] = gMonIcon_SteelixMega,
    [SPECIES_SCIZOR_MEGA] = gMonIcon_ScizorMega,
    [SPECIES_HERACROSS_MEGA] = gMonIcon_HeracrossMega,
    [SPECIES_HOUNDOOM_MEGA] = gMonIcon_HoundoomMega,
    [SPECIES_TYRANITAR_MEGA] = gMonIcon_TyranitarMega,
    [SPECIES_SCEPTILE_MEGA] = gMonIcon_SceptileMega,
    [SPECIES_BLAZIKEN_MEGA] = gMonIcon_BlazikenMega,
    [SPECIES_SWAMPERT_MEGA] = gMonIcon_SwampertMega,
    [SPECIES_GARDEVOIR_MEGA] = gMonIcon_GardevoirMega,
    [SPECIES_SABLEYE_MEGA] = gMonIcon_SableyeMega,
    [SPECIES_MAWILE_MEGA] = gMonIcon_MawileMega,
    [SPECIES_AGGRON_MEGA] = gMonIcon_AggronMega,
    [SPECIES_MEDICHAM_MEGA] = gMonIcon_MedichamMega,
    [SPECIES_MANECTRIC_MEGA] = gMonIcon_ManectricMega,
    [SPECIES_SHARPEDO_MEGA] = gMonIcon_SharpedoMega,
    [SPECIES_CAMERUPT_MEGA] = gMonIcon_CameruptMega,
    [SPECIES_ALTARIA_MEGA] = gMonIcon_AltariaMega,
    [SPECIES_BANETTE_MEGA] = gMonIcon_BanetteMega,
    [SPECIES_ABSOL_MEGA] = gMonIcon_AbsolMega,
    [SPECIES_GLALIE_MEGA] = gMonIcon_GlalieMega,
    [SPECIES_SALAMENCE_MEGA] = gMonIcon_SalamenceMega,
    [SPECIES_METAGROSS_MEGA] = gMonIcon_MetagrossMega,
    [SPECIES_LATIAS_MEGA] = gMonIcon_LatiasMega,
    [SPECIES_LATIOS_MEGA] = gMonIcon_LatiosMega,
    [SPECIES_LOPUNNY_MEGA] = gMonIcon_LopunnyMega,
    [SPECIES_GARCHOMP_MEGA] = gMonIcon_GarchompMega,
    [SPECIES_LUCARIO_MEGA] = gMonIcon_LucarioMega,
    [SPECIES_ABOMASNOW_MEGA] = gMonIcon_AbomasnowMega,
    [SPECIES_GALLADE_MEGA] = gMonIcon_GalladeMega,
    [SPECIES_AUDINO_MEGA] = gMonIcon_AudinoMega,
    [SPECIES_DIANCIE_MEGA] = gMonIcon_DiancieMega,
    [SPECIES_RAYQUAZA_MEGA] = gMonIcon_RayquazaMega,
    [SPECIES_KYOGRE_PRIMAL] = gMonIcon_KyogrePrimal,
    [SPECIES_GROUDON_PRIMAL] = gMonIcon_GroudonPrimal,
    [SPECIES_RATTATA_ALOLAN] = gMonIcon_RattataAlolan,
    [SPECIES_RATICATE_ALOLAN] = gMonIcon_RaticateAlolan,
    [SPECIES_RAICHU_ALOLAN] = gMonIcon_RaichuAlolan,
    [SPECIES_SANDSHREW_ALOLAN] = gMonIcon_SandshrewAlolan,
    [SPECIES_SANDSLASH_ALOLAN] = gMonIcon_SandslashAlolan,
    [SPECIES_VULPIX_ALOLAN] = gMonIcon_VulpixAlolan,
    [SPECIES_NINETALES_ALOLAN] = gMonIcon_NinetalesAlolan,
    [SPECIES_DIGLETT_ALOLAN] = gMonIcon_DiglettAlolan,
    [SPECIES_DUGTRIO_ALOLAN] = gMonIcon_DugtrioAlolan,
    [SPECIES_MEOWTH_ALOLAN] = gMonIcon_MeowthAlolan,
    [SPECIES_PERSIAN_ALOLAN] = gMonIcon_PersianAlolan,
    [SPECIES_GEODUDE_ALOLAN] = gMonIcon_GeodudeAlolan,
    [SPECIES_GRAVELER_ALOLAN] = gMonIcon_GravelerAlolan,
    [SPECIES_GOLEM_ALOLAN] = gMonIcon_GolemAlolan,
    [SPECIES_GRIMER_ALOLAN] = gMonIcon_GrimerAlolan,
    [SPECIES_MUK_ALOLAN] = gMonIcon_MukAlolan,
    [SPECIES_EXEGGUTOR_ALOLAN] = gMonIcon_ExeggutorAlolan,
    [SPECIES_MAROWAK_ALOLAN] = gMonIcon_MarowakAlolan,
    [SPECIES_MEOWTH_GALARIAN] = gMonIcon_MeowthGalarian,
    [SPECIES_PONYTA_GALARIAN] = gMonIcon_PonytaGalarian,
    [SPECIES_RAPIDASH_GALARIAN] = gMonIcon_RapidashGalarian,
    [SPECIES_SLOWPOKE_GALARIAN] = gMonIcon_SlowpokeGalarian,
    [SPECIES_SLOWBRO_GALARIAN] = gMonIcon_SlowbroGalarian,
    [SPECIES_FARFETCHD_GALARIAN] = gMonIcon_FarfetchdGalarian,
    [SPECIES_WEEZING_GALARIAN] = gMonIcon_WeezingGalarian,
    [SPECIES_MR_MIME_GALARIAN] = gMonIcon_MrMimeGalarian,
    [SPECIES_ARTICUNO_GALARIAN] = gMonIcon_ArticunoGalarian,
    [SPECIES_ZAPDOS_GALARIAN] = gMonIcon_ZapdosGalarian,
    [SPECIES_MOLTRES_GALARIAN] = gMonIcon_MoltresGalarian,
    [SPECIES_SLOWKING_GALARIAN] = gMonIcon_SlowkingGalarian,
    [SPECIES_CORSOLA_GALARIAN] = gMonIcon_CorsolaGalarian,
    [SPECIES_ZIGZAGOON_GALARIAN] = gMonIcon_ZigzagoonGalarian,
    [SPECIES_LINOONE_GALARIAN] = gMonIcon_LinooneGalarian,
    [SPECIES_DARUMAKA_GALARIAN] = gMonIcon_DarumakaGalarian,
    [SPECIES_DARMANITAN_GALARIAN_STANDARD_MODE] = gMonIcon_DarmanitanGalarianStandardMode,
    [SPECIES_YAMASK_GALARIAN] = gMonIcon_YamaskGalarian,
    [SPECIES_STUNFISK_GALARIAN] = gMonIcon_StunfiskGalarian,
    [SPECIES_GROWLITHE_HISUIAN] = gMonIcon_GrowlitheHisuian,
    [SPECIES_ARCANINE_HISUIAN] = gMonIcon_ArcanineHisuian,
    [SPECIES_VOLTORB_HISUIAN] = gMonIcon_VoltorbHisuian,
    [SPECIES_ELECTRODE_HISUIAN] = gMonIcon_ElectrodeHisuian,
    [SPECIES_TYPHLOSION_HISUIAN] = gMonIcon_TyphlosionHisuian,
    [SPECIES_QWILFISH_HISUIAN] = gMonIcon_QwilfishHisuian,
    [SPECIES_SNEASEL_HISUIAN] = gMonIcon_SneaselHisuian,
    [SPECIES_SAMUROTT_HISUIAN] = gMonIcon_SamurottHisuian,
    [SPECIES_LILLIGANT_HISUIAN] = gMonIcon_LilligantHisuian,
    [SPECIES_ZORUA_HISUIAN] = gMonIcon_ZoruaHisuian,
    [SPECIES_ZOROARK_HISUIAN] = gMonIcon_ZoroarkHisuian,
    [SPECIES_BRAVIARY_HISUIAN] = gMonIcon_BraviaryHisuian,
    [SPECIES_SLIGGOO_HISUIAN] = gMonIcon_SliggooHisuian,
    [SPECIES_GOODRA_HISUIAN] = gMonIcon_GoodraHisuian,
    [SPECIES_AVALUGG_HISUIAN] = gMonIcon_AvaluggHisuian,
    [SPECIES_DECIDUEYE_HISUIAN] = gMonIcon_DecidueyeHisuian,
    [SPECIES_PIKACHU_COSPLAY] = gMonIcon_PikachuCosplay,
    [SPECIES_PIKACHU_ROCK_STAR] = gMonIcon_PikachuRockStar,
    [SPECIES_PIKACHU_BELLE] = gMonIcon_PikachuBelle,
    [SPECIES_PIKACHU_POP_STAR] = gMonIcon_PikachuPopStar,
    [SPECIES_PIKACHU_PH_D] = gMonIcon_PikachuPhD,
    [SPECIES_PIKACHU_LIBRE] = gMonIcon_PikachuLibre,
    [SPECIES_PIKACHU_ORIGINAL_CAP] = gMonIcon_PikachuOriginalCap,
    [SPECIES_PIKACHU_HOENN_CAP] = gMonIcon_PikachuHoennCap,
    [SPECIES_PIKACHU_SINNOH_CAP] = gMonIcon_PikachuSinnohCap,
    [SPECIES_PIKACHU_UNOVA_CAP] = gMonIcon_PikachuUnovaCap,
    [SPECIES_PIKACHU_KALOS_CAP] = gMonIcon_PikachuKalosCap,
    [SPECIES_PIKACHU_ALOLA_CAP] = gMonIcon_PikachuAlolaCap,
    [SPECIES_PIKACHU_PARTNER_CAP] = gMonIcon_PikachuPartnerCap,
    [SPECIES_PIKACHU_WORLD_CAP] = gMonIcon_PikachuWorldCap,
    [SPECIES_PICHU_SPIKY_EARED] = gMonIcon_PichuSpikyEared,
    [SPECIES_UNOWN_B] = gMonIcon_UnownB,
    [SPECIES_UNOWN_C] = gMonIcon_UnownC,
    [SPECIES_UNOWN_D] = gMonIcon_UnownD,
    [SPECIES_UNOWN_E] = gMonIcon_UnownE,
    [SPECIES_UNOWN_F] = gMonIcon_UnownF,
    [SPECIES_UNOWN_G] = gMonIcon_UnownG,
    [SPECIES_UNOWN_H] = gMonIcon_UnownH,
    [SPECIES_UNOWN_I] = gMonIcon_UnownI,
    [SPECIES_UNOWN_J] = gMonIcon_UnownJ,
    [SPECIES_UNOWN_K] = gMonIcon_UnownK,
    [SPECIES_UNOWN_L] = gMonIcon_UnownL,
    [SPECIES_UNOWN_M] = gMonIcon_UnownM,
    [SPECIES_UNOWN_N] = gMonIcon_UnownN,
    [SPECIES_UNOWN_O] = gMonIcon_UnownO,
    [SPECIES_UNOWN_P] = gMonIcon_UnownP,
    [SPECIES_UNOWN_Q] = gMonIcon_UnownQ,
    [SPECIES_UNOWN_R] = gMonIcon_UnownR,
    [SPECIES_UNOWN_S] = gMonIcon_UnownS,
    [SPECIES_UNOWN_T] = gMonIcon_UnownT,
    [SPECIES_UNOWN_U] = gMonIcon_UnownU,
    [SPECIES_UNOWN_V] = gMonIcon_UnownV,
    [SPECIES_UNOWN_W] = gMonIcon_UnownW,
    [SPECIES_UNOWN_X] = gMonIcon_UnownX,
    [SPECIES_UNOWN_Y] = gMonIcon_UnownY,
    [SPECIES_UNOWN_Z] = gMonIcon_UnownZ,
    [SPECIES_UNOWN_EMARK] = gMonIcon_UnownExclamationMark,
    [SPECIES_UNOWN_QMARK] = gMonIcon_UnownQuestionMark,
    [SPECIES_CASTFORM_SUNNY] = gMonIcon_CastformSunny,
    [SPECIES_CASTFORM_RAINY] = gMonIcon_CastformRainy,
    [SPECIES_CASTFORM_SNOWY] = gMonIcon_CastformSnowy,
    [SPECIES_DEOXYS_ATTACK] = gMonIcon_DeoxysAttack,
    [SPECIES_DEOXYS_DEFENSE] = gMonIcon_DeoxysDefense,
    [SPECIES_DEOXYS_SPEED] = gMonIcon_DeoxysSpeed,
    [SPECIES_BURMY_SANDY_CLOAK] = gMonIcon_BurmySandyCloak,
    [SPECIES_BURMY_TRASH_CLOAK] = gMonIcon_BurmyTrashCloak,
    [SPECIES_WORMADAM_SANDY_CLOAK] = gMonIcon_WormadamSandyCloak,
    [SPECIES_WORMADAM_TRASH_CLOAK] = gMonIcon_WormadamTrashCloak,
    [SPECIES_CHERRIM_SUNSHINE] = gMonIcon_CherrimSunshine,
    [SPECIES_SHELLOS_EAST_SEA] = gMonIcon_ShellosEastSea,
    [SPECIES_GASTRODON_EAST_SEA] = gMonIcon_GastrodonEastSea,
    [SPECIES_ROTOM_HEAT] = gMonIcon_RotomHeat,
    [SPECIES_ROTOM_WASH] = gMonIcon_RotomWash,
    [SPECIES_ROTOM_FROST] = gMonIcon_RotomFrost,
    [SPECIES_ROTOM_FAN] = gMonIcon_RotomFan,
    [SPECIES_ROTOM_MOW] = gMonIcon_RotomMow,
    [SPECIES_DIALGA_ORIGIN] = gMonIcon_DialgaOrigin,
    [SPECIES_PALKIA_ORIGIN] = gMonIcon_PalkiaOrigin,
    [SPECIES_GIRATINA_ORIGIN] = gMonIcon_GiratinaOrigin,
    [SPECIES_SHAYMIN_SKY] = gMonIcon_ShayminSky,
    [SPECIES_ARCEUS_FIGHTING] = gMonIcon_Arceus,
    [SPECIES_ARCEUS_FLYING] = gMonIcon_Arceus,
    [SPECIES_ARCEUS_POISON] = gMonIcon_Arceus,
    [SPECIES_ARCEUS_GROUND] = gMonIcon_Arceus,
    [SPECIES_ARCEUS_ROCK] = gMonIcon_Arceus,
    [SPECIES_ARCEUS_BUG] = gMonIcon_Arceus,
    [SPECIES_ARCEUS_GHOST] = gMonIcon_Arceus,
    [SPECIES_ARCEUS_STEEL] = gMonIcon_Arceus,
    [SPECIES_ARCEUS_FIRE] = gMonIcon_Arceus,
    [SPECIES_ARCEUS_WATER] = gMonIcon_Arceus,
    [SPECIES_ARCEUS_GRASS] = gMonIcon_Arceus,
    [SPECIES_ARCEUS_ELECTRIC] = gMonIcon_Arceus,
    [SPECIES_ARCEUS_PSYCHIC] = gMonIcon_Arceus,
    [SPECIES_ARCEUS_ICE] = gMonIcon_Arceus,
    [SPECIES_ARCEUS_DRAGON] = gMonIcon_Arceus,
    [SPECIES_ARCEUS_DARK] = gMonIcon_Arceus,
    [SPECIES_ARCEUS_FAIRY] = gMonIcon_Arceus,
    [SPECIES_BASCULIN_BLUE_STRIPED] = gMonIcon_BasculinBlueStriped,
    [SPECIES_BASCULIN_WHITE_STRIPED] = gMonIcon_BasculinWhiteStriped,
    [SPECIES_DARMANITAN_ZEN_MODE] = gMonIcon_DarmanitanZenMode,
    [SPECIES_DARMANITAN_GALARIAN_ZEN_MODE] = gMonIcon_DarmanitanGalarianZenMode,
    [SPECIES_DEERLING_SUMMER] = gMonIcon_DeerlingSummer,
    [SPECIES_DEERLING_AUTUMN] = gMonIcon_DeerlingAutumn,
    [SPECIES_DEERLING_WINTER] = gMonIcon_DeerlingWinter,
    [SPECIES_SAWSBUCK_SUMMER] = gMonIcon_SawsbuckSummer,
    [SPECIES_SAWSBUCK_AUTUMN] = gMonIcon_SawsbuckAutumn,
    [SPECIES_SAWSBUCK_WINTER] = gMonIcon_SawsbuckWinter,
    [SPECIES_TORNADUS_THERIAN] = gMonIcon_TornadusTherian,
    [SPECIES_THUNDURUS_THERIAN] = gMonIcon_ThundurusTherian,
    [SPECIES_LANDORUS_THERIAN] = gMonIcon_LandorusTherian,
    [SPECIES_KYUREM_WHITE] = gMonIcon_KyuremWhite,
    [SPECIES_KYUREM_BLACK] = gMonIcon_KyuremBlack,
    [SPECIES_KELDEO_RESOLUTE] = gMonIcon_KeldeoResolute,
    [SPECIES_MELOETTA_PIROUETTE] = gMonIcon_MeloettaPirouette,
    [SPECIES_GENESECT_DOUSE_DRIVE] = gMonIcon_Genesect,
    [SPECIES_GENESECT_SHOCK_DRIVE] = gMonIcon_Genesect,
    [SPECIES_GENESECT_BURN_DRIVE] = gMonIcon_Genesect,
    [SPECIES_GENESECT_CHILL_DRIVE] = gMonIcon_Genesect,
    [SPECIES_GRENINJA_BATTLE_BOND] = gMonIcon_Greninja,
    [SPECIES_GRENINJA_ASH] = gMonIcon_GreninjaAsh,
    [SPECIES_VIVILLON_POLAR] = gMonIcon_VivillonPolar,
    [SPECIES_VIVILLON_TUNDRA] = gMonIcon_VivillonTundra,
    [SPECIES_VIVILLON_CONTINENTAL] = gMonIcon_VivillonContinental,
    [SPECIES_VIVILLON_GARDEN] = gMonIcon_VivillonGarden,
    [SPECIES_VIVILLON_ELEGANT] = gMonIcon_VivillonElegant,
    [SPECIES_VIVILLON_MEADOW] = gMonIcon_VivillonMeadow,
    [SPECIES_VIVILLON_MODERN] = gMonIcon_VivillonModern,
    [SPECIES_VIVILLON_MARINE] = gMonIcon_VivillonMarine,
    [SPECIES_VIVILLON_ARCHIPELAGO] = gMonIcon_VivillonArchipelago,
    [SPECIES_VIVILLON_HIGH_PLAINS] = gMonIcon_VivillonHighPlains,
    [SPECIES_VIVILLON_SANDSTORM] = gMonIcon_VivillonSandstorm,
    [SPECIES_VIVILLON_RIVER] = gMonIcon_VivillonRiver,
    [SPECIES_VIVILLON_MONSOON] = gMonIcon_VivillonMonsoon,
    [SPECIES_VIVILLON_SAVANNA] = gMonIcon_VivillonSavanna,
    [SPECIES_VIVILLON_SUN] = gMonIcon_VivillonSun,
    [SPECIES_VIVILLON_OCEAN] = gMonIcon_VivillonOcean,
    [SPECIES_VIVILLON_JUNGLE] = gMonIcon_VivillonJungle,
    [SPECIES_VIVILLON_FANCY] = gMonIcon_VivillonFancy,
    [SPECIES_VIVILLON_POKE_BALL] = gMonIcon_VivillonPokeBall,
    [SPECIES_FLABEBE_YELLOW_FLOWER] = gMonIcon_FlabebeYellowFlower,
    [SPECIES_FLABEBE_ORANGE_FLOWER] = gMonIcon_FlabebeOrangeFlower,
    [SPECIES_FLABEBE_BLUE_FLOWER] = gMonIcon_FlabebeBlueFlower,
    [SPECIES_FLABEBE_WHITE_FLOWER] = gMonIcon_FlabebeWhiteFlower,
    [SPECIES_FLOETTE_YELLOW_FLOWER] = gMonIcon_FloetteYellowFlower,
    [SPECIES_FLOETTE_ORANGE_FLOWER] = gMonIcon_FloetteOrangeFlower,
    [SPECIES_FLOETTE_BLUE_FLOWER] = gMonIcon_FloetteBlueFlower,
    [SPECIES_FLOETTE_WHITE_FLOWER] = gMonIcon_FloetteWhiteFlower,
    [SPECIES_FLOETTE_ETERNAL_FLOWER] = gMonIcon_FloetteEternalFlower,
    [SPECIES_FLORGES_YELLOW_FLOWER] = gMonIcon_FlorgesYellowFlower,
    [SPECIES_FLORGES_ORANGE_FLOWER] = gMonIcon_FlorgesOrangeFlower,
    [SPECIES_FLORGES_BLUE_FLOWER] = gMonIcon_FlorgesBlueFlower,
    [SPECIES_FLORGES_WHITE_FLOWER] = gMonIcon_FlorgesWhiteFlower,
    [SPECIES_FURFROU_HEART_TRIM] = gMonIcon_FurfrouHeartTrim,
    [SPECIES_FURFROU_STAR_TRIM] = gMonIcon_FurfrouStarTrim,
    [SPECIES_FURFROU_DIAMOND_TRIM] = gMonIcon_FurfrouDiamondTrim,
    [SPECIES_FURFROU_DEBUTANTE_TRIM] = gMonIcon_FurfrouDebutanteTrim,
    [SPECIES_FURFROU_MATRON_TRIM] = gMonIcon_FurfrouMatronTrim,
    [SPECIES_FURFROU_DANDY_TRIM] = gMonIcon_FurfrouDandyTrim,
    [SPECIES_FURFROU_LA_REINE_TRIM] = gMonIcon_FurfrouLaReineTrim,
    [SPECIES_FURFROU_KABUKI_TRIM] = gMonIcon_FurfrouKabukiTrim,
    [SPECIES_FURFROU_PHARAOH_TRIM] = gMonIcon_FurfrouPharaohTrim,
    [SPECIES_MEOWSTIC_FEMALE] = gMonIcon_MeowsticFemale,
    [SPECIES_AEGISLASH_BLADE] = gMonIcon_AegislashBlade,
    [SPECIES_PUMPKABOO_SMALL] = gMonIcon_Pumpkaboo,
    [SPECIES_PUMPKABOO_LARGE] = gMonIcon_Pumpkaboo,
    [SPECIES_PUMPKABOO_SUPER] = gMonIcon_Pumpkaboo,
    [SPECIES_GOURGEIST_SMALL] = gMonIcon_Gourgeist,
    [SPECIES_GOURGEIST_LARGE] = gMonIcon_Gourgeist,
    [SPECIES_GOURGEIST_SUPER] = gMonIcon_Gourgeist,
    [SPECIES_XERNEAS_ACTIVE] = gMonIcon_XerneasActive,
    [SPECIES_ZYGARDE_10_AURA_BREAK] = gMonIcon_Zygarde10,
    [SPECIES_ZYGARDE_10_POWER_CONSTRUCT] = gMonIcon_Zygarde10,
    [SPECIES_ZYGARDE_50_POWER_CONSTRUCT] = gMonIcon_Zygarde50,
    [SPECIES_ZYGARDE_COMPLETE] = gMonIcon_ZygardeComplete,
    [SPECIES_HOOPA_UNBOUND] = gMonIcon_HoopaUnbound,
    [SPECIES_ORICORIO_POM_POM] = gMonIcon_OricorioPomPom,
    [SPECIES_ORICORIO_PAU] = gMonIcon_OricorioPau,
    [SPECIES_ORICORIO_SENSU] = gMonIcon_OricorioSensu,
    [SPECIES_ROCKRUFF_OWN_TEMPO] = gMonIcon_Rockruff,
    [SPECIES_LYCANROC_MIDNIGHT] = gMonIcon_LycanrocMidnight,
    [SPECIES_LYCANROC_DUSK] = gMonIcon_LycanrocDusk,
    [SPECIES_WISHIWASHI_SCHOOL] = gMonIcon_WishiwashiSchool,
    [SPECIES_SILVALLY_FIGHTING] = gMonIcon_Silvally,
    [SPECIES_SILVALLY_FLYING] = gMonIcon_Silvally,
    [SPECIES_SILVALLY_POISON] = gMonIcon_Silvally,
    [SPECIES_SILVALLY_GROUND] = gMonIcon_Silvally,
    [SPECIES_SILVALLY_ROCK] = gMonIcon_Silvally,
    [SPECIES_SILVALLY_BUG] = gMonIcon_Silvally,
    [SPECIES_SILVALLY_GHOST] = gMonIcon_Silvally,
    [SPECIES_SILVALLY_STEEL] = gMonIcon_Silvally,
    [SPECIES_SILVALLY_FIRE] = gMonIcon_Silvally,
    [SPECIES_SILVALLY_WATER] = gMonIcon_Silvally,
    [SPECIES_SILVALLY_GRASS] = gMonIcon_Silvally,
    [SPECIES_SILVALLY_ELECTRIC] = gMonIcon_Silvally,
    [SPECIES_SILVALLY_PSYCHIC] = gMonIcon_Silvally,
    [SPECIES_SILVALLY_ICE] = gMonIcon_Silvally,
    [SPECIES_SILVALLY_DRAGON] = gMonIcon_Silvally,
    [SPECIES_SILVALLY_DARK] = gMonIcon_Silvally,
    [SPECIES_SILVALLY_FAIRY] = gMonIcon_Silvally,
    [SPECIES_MINIOR_METEOR_ORANGE] = gMonIcon_MiniorMeteor,
    [SPECIES_MINIOR_METEOR_YELLOW] = gMonIcon_MiniorMeteor,
    [SPECIES_MINIOR_METEOR_GREEN] = gMonIcon_MiniorMeteor,
    [SPECIES_MINIOR_METEOR_BLUE] = gMonIcon_MiniorMeteor,
    [SPECIES_MINIOR_METEOR_INDIGO] = gMonIcon_MiniorMeteor,
    [SPECIES_MINIOR_METEOR_VIOLET] = gMonIcon_MiniorMeteor,
    [SPECIES_MINIOR_CORE_RED] = gMonIcon_MiniorCoreRed,
    [SPECIES_MINIOR_CORE_ORANGE] = gMonIcon_MiniorCoreOrange,
    [SPECIES_MINIOR_CORE_YELLOW] = gMonIcon_MiniorCoreYellow,
    [SPECIES_MINIOR_CORE_GREEN] = gMonIcon_MiniorCoreGreen,
    [SPECIES_MINIOR_CORE_BLUE] = gMonIcon_MiniorCoreBlue,
    [SPECIES_MINIOR_CORE_INDIGO] = gMonIcon_MiniorCoreIndigo,
    [SPECIES_MINIOR_CORE_VIOLET] = gMonIcon_MiniorCoreViolet,
    [SPECIES_MIMIKYU_BUSTED] = gMonIcon_MimikyuBusted,
    [SPECIES_NECROZMA_DUSK_MANE] = gMonIcon_NecrozmaDuskMane,
    [SPECIES_NECROZMA_DAWN_WINGS] = gMonIcon_NecrozmaDawnWings,
    [SPECIES_NECROZMA_ULTRA] = gMonIcon_NecrozmaUltra,
    [SPECIES_MAGEARNA_ORIGINAL_COLOR] = gMonIcon_MagearnaOriginalColor,
    [SPECIES_CRAMORANT_GULPING] = gMonIcon_CramorantGulping,
    [SPECIES_CRAMORANT_GORGING] = gMonIcon_CramorantGorging,
    [SPECIES_TOXTRICITY_LOW_KEY] = gMonIcon_ToxtricityLowKey,
    [SPECIES_SINISTEA_ANTIQUE] = gMonIcon_Sinistea,
    [SPECIES_POLTEAGEIST_ANTIQUE] = gMonIcon_Polteageist,
    [SPECIES_EISCUE_NOICE_FACE] = gMonIcon_EiscueNoiceFace,
    [SPECIES_INDEEDEE_FEMALE] = gMonIcon_IndeedeeFemale,
    [SPECIES_MORPEKO_HANGRY] = gMonIcon_MorpekoHangry,
    [SPECIES_ZACIAN_CROWNED_SWORD] = gMonIcon_ZacianCrownedSword,
    [SPECIES_ZAMAZENTA_CROWNED_SHIELD] = gMonIcon_ZamazentaCrownedShield,
    [SPECIES_ETERNATUS_ETERNAMAX] = gMonIcon_EternatusEternamax,
    [SPECIES_URSHIFU_RAPID_STRIKE_STYLE] = gMonIcon_UrshifuSingleStrikeStyle,
    [SPECIES_ZARUDE_DADA] = gMonIcon_ZarudeDada,
    [SPECIES_CALYREX_ICE_RIDER] = gMonIcon_CalyrexIceRider,
    [SPECIES_CALYREX_SHADOW_RIDER] = gMonIcon_CalyrexShadowRider,
    [SPECIES_ENAMORUS_THERIAN] = gMonIcon_EnamorusTherian,
    [SPECIES_BASCULEGION_FEMALE] = gMonIcon_BasculegionFemale,
    // Gigantamax Forms
    [SPECIES_VENUSAUR_GIGANTAMAX] = gMonIcon_VenusaurGigantamax,
    [SPECIES_CHARIZARD_GIGANTAMAX] = gMonIcon_CharizardGigantamax,
    [SPECIES_BLASTOISE_GIGANTAMAX] = gMonIcon_BlastoiseGigantamax,
    [SPECIES_BUTTERFREE_GIGANTAMAX] = gMonIcon_ButterfreeGigantamax,
    [SPECIES_PIKACHU_GIGANTAMAX] = gMonIcon_PikachuGigantamax,
    [SPECIES_MEOWTH_GIGANTAMAX] = gMonIcon_MeowthGigantamax,
    [SPECIES_MACHAMP_GIGANTAMAX] = gMonIcon_MachampGigantamax,
    [SPECIES_GENGAR_GIGANTAMAX] = gMonIcon_GengarGigantamax,
    [SPECIES_KINGLER_GIGANTAMAX] = gMonIcon_KinglerGigantamax,
    [SPECIES_LAPRAS_GIGANTAMAX] = gMonIcon_LaprasGigantamax,
    [SPECIES_EEVEE_GIGANTAMAX] = gMonIcon_EeveeGigantamax,
    [SPECIES_SNORLAX_GIGANTAMAX] = gMonIcon_SnorlaxGigantamax,
    [SPECIES_GARBODOR_GIGANTAMAX] = gMonIcon_GarbodorGigantamax,
    [SPECIES_MELMETAL_GIGANTAMAX] = gMonIcon_MelmetalGigantamax,
    [SPECIES_RILLABOOM_GIGANTAMAX] = gMonIcon_RillaboomGigantamax,
    [SPECIES_CINDERACE_GIGANTAMAX] = gMonIcon_CinderaceGigantamax,
    [SPECIES_INTELEON_GIGANTAMAX] = gMonIcon_InteleonGigantamax,
    [SPECIES_CORVIKNIGHT_GIGANTAMAX] = gMonIcon_CorviknightGigantamax,
    [SPECIES_ORBEETLE_GIGANTAMAX] = gMonIcon_OrbeetleGigantamax,
    [SPECIES_DREDNAW_GIGANTAMAX] = gMonIcon_DrednawGigantamax,
    [SPECIES_COALOSSAL_GIGANTAMAX] = gMonIcon_CoalossalGigantamax,
    [SPECIES_FLAPPLE_GIGANTAMAX] = gMonIcon_FlappleGigantamax,
    [SPECIES_APPLETUN_GIGANTAMAX] = gMonIcon_AppletunGigantamax,
    [SPECIES_SANDACONDA_GIGANTAMAX] = gMonIcon_SandacondaGigantamax,
    [SPECIES_TOXTRICITY_AMPED_GIGANTAMAX] = gMonIcon_ToxtricityGigantamax,
    [SPECIES_TOXTRICITY_LOW_KEY_GIGANTAMAX] = gMonIcon_ToxtricityGigantamax,
    [SPECIES_CENTISKORCH_GIGANTAMAX] = gMonIcon_CentiskorchGigantamax,
    [SPECIES_HATTERENE_GIGANTAMAX] = gMonIcon_HattereneGigantamax,
    [SPECIES_GRIMMSNARL_GIGANTAMAX] = gMonIcon_GrimmsnarlGigantamax,
    [SPECIES_ALCREMIE_GIGANTAMAX] = gMonIcon_AlcremieGigantamax,
    [SPECIES_COPPERAJAH_GIGANTAMAX] = gMonIcon_CopperajahGigantamax,
    [SPECIES_DURALUDON_GIGANTAMAX] = gMonIcon_DuraludonGigantamax,
    [SPECIES_URSHIFU_SINGLE_STRIKE_STYLE_GIGANTAMAX] = gMonIcon_UrshifuSingleStrikeGigantamax,
    [SPECIES_URSHIFU_RAPID_STRIKE_STYLE_GIGANTAMAX] = gMonIcon_UrshifuRapidStrikeGigantamax,
    [SPECIES_SPRIGATITO] = gMonIcon_Sprigatito,
    [SPECIES_FLORAGATO] = gMonIcon_Floragato,
    [SPECIES_MEOWSCARADA] = gMonIcon_Meowscarada,
    [SPECIES_FUECOCO] = gMonIcon_Fuecoco,
    [SPECIES_CROCALOR] = gMonIcon_Crocalor,
    [SPECIES_SKELEDIRGE] = gMonIcon_Skeledirge,
    [SPECIES_QUAXLY] = gMonIcon_Quaxly,
    [SPECIES_QUAXWELL] = gMonIcon_Quaxwell,
    [SPECIES_QUAQUAVAL] = gMonIcon_Quaquaval,
    [SPECIES_LECHONK] = gMonIcon_Lechonk,
    [SPECIES_OINKOLOGNE_MALE] = gMonIcon_OinkologneMale,
    [SPECIES_OINKOLOGNE_FEMALE] = gMonIcon_OinkologneFemale,
    [SPECIES_TAROUNTULA] = gMonIcon_Tarountula,
    [SPECIES_SPIDOPS] = gMonIcon_Spidops,
    [SPECIES_NYMBLE] = gMonIcon_Nymble,
    [SPECIES_LOKIX] = gMonIcon_Lokix,
    [SPECIES_PAWMI] = gMonIcon_Pawmi,
    [SPECIES_PAWMO] = gMonIcon_Pawmo,
    [SPECIES_PAWMOT] = gMonIcon_Pawmot,
    [SPECIES_TANDEMAUS] = gMonIcon_Tandemaus,
    [SPECIES_MAUSHOLD_FAMILY_OF_THREE] = gMonIcon_MausholdFamilyOfThree,
    [SPECIES_MAUSHOLD_FAMILY_OF_FOUR] = gMonIcon_MausholdFamilyOfFour,
    [SPECIES_FIDOUGH] = gMonIcon_Fidough,
    [SPECIES_DACHSBUN] = gMonIcon_Dachsbun,
    [SPECIES_SMOLIV] = gMonIcon_Smoliv,
    [SPECIES_DOLLIV] = gMonIcon_Dolliv,
    [SPECIES_ARBOLIVA] = gMonIcon_Arboliva,
    [SPECIES_SQUAWKABILLY_GREEN_PLUMAGE] = gMonIcon_SquawkabillyGreenPlumage,
    [SPECIES_SQUAWKABILLY_BLUE_PLUMAGE] = gMonIcon_SquawkabillyBluePlumage,
    [SPECIES_SQUAWKABILLY_YELLOW_PLUMAGE] = gMonIcon_SquawkabillyYellowPlumage,
    [SPECIES_SQUAWKABILLY_WHITE_PLUMAGE] = gMonIcon_SquawkabillyWhitePlumage,
    [SPECIES_NACLI] = gMonIcon_Nacli,
    [SPECIES_NACLSTACK] = gMonIcon_Naclstack,
    [SPECIES_GARGANACL] = gMonIcon_Garganacl,
    [SPECIES_CHARCADET] = gMonIcon_Charcadet,
    [SPECIES_ARMAROUGE] = gMonIcon_Armarouge,
    [SPECIES_CERULEDGE] = gMonIcon_Ceruledge,
    [SPECIES_TADBULB] = gMonIcon_Tadbulb,
    [SPECIES_BELLIBOLT] = gMonIcon_Bellibolt,
    [SPECIES_WATTREL] = gMonIcon_Wattrel,
    [SPECIES_KILOWATTREL] = gMonIcon_Kilowattrel,
    [SPECIES_MASCHIFF] = gMonIcon_Maschiff,
    [SPECIES_MABOSSTIFF] = gMonIcon_Mabosstiff,
    [SPECIES_SHROODLE] = gMonIcon_Shroodle,
    [SPECIES_GRAFAIAI] = gMonIcon_Grafaiai,
    [SPECIES_BRAMBLIN] = gMonIcon_Bramblin,
    [SPECIES_BRAMBLEGHAST] = gMonIcon_Brambleghast,
    [SPECIES_TOEDSCOOL] = gMonIcon_Toedscool,
    [SPECIES_TOEDSCRUEL] = gMonIcon_Toedscruel,
    [SPECIES_KLAWF] = gMonIcon_Klawf,
    [SPECIES_CAPSAKID] = gMonIcon_Capsakid,
    [SPECIES_SCOVILLAIN] = gMonIcon_Scovillain,
    [SPECIES_RELLOR] = gMonIcon_Rellor,
    [SPECIES_RABSCA] = gMonIcon_Rabsca,
    [SPECIES_FLITTLE] = gMonIcon_Flittle,
    [SPECIES_ESPATHRA] = gMonIcon_Espathra,
    [SPECIES_TINKATINK] = gMonIcon_Tinkatink,
    [SPECIES_TINKATUFF] = gMonIcon_Tinkatuff,
    [SPECIES_TINKATON] = gMonIcon_Tinkaton,
    [SPECIES_WIGLETT] = gMonIcon_Wiglett,
    [SPECIES_WUGTRIO] = gMonIcon_Wugtrio,
    [SPECIES_BOMBIRDIER] = gMonIcon_Bombirdier,
    [SPECIES_FINIZEN] = gMonIcon_Finizen,
    [SPECIES_PALAFIN_ZERO] = gMonIcon_PalafinZero,
    [SPECIES_PALAFIN_HERO] = gMonIcon_PalafinHero,
    [SPECIES_VAROOM] = gMonIcon_Varoom,
    [SPECIES_REVAVROOM] = gMonIcon_Revavroom,
    [SPECIES_CYCLIZAR] = gMonIcon_Cyclizar,
    [SPECIES_ORTHWORM] = gMonIcon_Orthworm,
    [SPECIES_GLIMMET] = gMonIcon_Glimmet,
    [SPECIES_GLIMMORA] = gMonIcon_Glimmora,
    [SPECIES_GREAVARD] = gMonIcon_Greavard,
    [SPECIES_HOUNDSTONE] = gMonIcon_Houndstone,
    [SPECIES_FLAMIGO] = gMonIcon_Flamigo,
    [SPECIES_CETODDLE] = gMonIcon_Cetoddle,
    [SPECIES_CETITAN] = gMonIcon_Cetitan,
    [SPECIES_VELUZA] = gMonIcon_Veluza,
    [SPECIES_DONDOZO] = gMonIcon_Dondozo,
    [SPECIES_TATSUGIRI_CURLY] = gMonIcon_TatsugiriCurly,
    [SPECIES_TATSUGIRI_DROOPY] = gMonIcon_TatsugiriDroopy,
    [SPECIES_TATSUGIRI_STRETCHY] = gMonIcon_TatsugiriStretchy,
    [SPECIES_ANNIHILAPE] = gMonIcon_Annihilape,
    [SPECIES_CLODSIRE] = gMonIcon_Clodsire,
    [SPECIES_FARIGIRAF] = gMonIcon_Farigiraf,
    [SPECIES_DUDUNSPARCE_TWO_SEGMENT] = gMonIcon_Dudunsparce,
    [SPECIES_DUDUNSPARCE_THREE_SEGMENT] = gMonIcon_Dudunsparce,
    [SPECIES_KINGAMBIT] = gMonIcon_Kingambit,
    [SPECIES_GREAT_TUSK] = gMonIcon_GreatTusk,
    [SPECIES_SCREAM_TAIL] = gMonIcon_ScreamTail,
    [SPECIES_BRUTE_BONNET] = gMonIcon_BruteBonnet,
    [SPECIES_FLUTTER_MANE] = gMonIcon_FlutterMane,
    [SPECIES_SLITHER_WING] = gMonIcon_SlitherWing,
    [SPECIES_SANDY_SHOCKS] = gMonIcon_SandyShocks,
    [SPECIES_IRON_TREADS] = gMonIcon_IronTreads,
    [SPECIES_IRON_BUNDLE] = gMonIcon_IronBundle,
    [SPECIES_IRON_HANDS] = gMonIcon_IronHands,
    [SPECIES_IRON_JUGULIS] = gMonIcon_IronJugulis,
    [SPECIES_IRON_MOTH] = gMonIcon_IronMoth,
    [SPECIES_IRON_THORNS] = gMonIcon_IronThorns,
    [SPECIES_FRIGIBAX] = gMonIcon_Frigibax,
    [SPECIES_ARCTIBAX] = gMonIcon_Arctibax,
    [SPECIES_BAXCALIBUR] = gMonIcon_Baxcalibur,
    [SPECIES_GIMMIGHOUL_CHEST] = gMonIcon_GimmighoulChest,
    [SPECIES_GIMMIGHOUL_ROAMING] = gMonIcon_GimmighoulRoaming,
    [SPECIES_GHOLDENGO] = gMonIcon_Gholdengo,
    [SPECIES_WO_CHIEN] = gMonIcon_WoChien,
    [SPECIES_CHIEN_PAO] = gMonIcon_ChienPao,
    [SPECIES_TING_LU] = gMonIcon_TingLu,
    [SPECIES_CHI_YU] = gMonIcon_ChiYu,
    [SPECIES_ROARING_MOON] = gMonIcon_RoaringMoon,
    [SPECIES_IRON_VALIANT] = gMonIcon_IronValiant,
    [SPECIES_KORAIDON] = gMonIcon_Koraidon,
    [SPECIES_MIRAIDON] = gMonIcon_Miraidon,
    [SPECIES_WALKING_WAKE] = gMonIcon_WalkingWake,
    [SPECIES_IRON_LEAVES] = gMonIcon_IronLeaves,
    [SPECIES_DIPPLIN] = gMonIcon_Dipplin,
    [SPECIES_POLTCHAGEIST_COUNTERFEIT] = gMonIcon_Poltchageist,
    [SPECIES_POLTCHAGEIST_ARTISAN] = gMonIcon_Poltchageist,
    [SPECIES_SINISTCHA_UNREMARKABLE] = gMonIcon_Sinistcha,
    [SPECIES_SINISTCHA_MASTERPIECE] = gMonIcon_Sinistcha,
    [SPECIES_OKIDOGI] = gMonIcon_Okidogi,
    [SPECIES_MUNKIDORI] = gMonIcon_Munkidori,
    [SPECIES_FEZANDIPITI] = gMonIcon_Fezandipiti,
    [SPECIES_OGERPON_TEAL_MASK] = gMonIcon_OgerponTealMask,
    //[SPECIES_OGERPON_WELLSPRING_MASK] = gMonIcon_OgerponWellspringMask, TODO
    //[SPECIES_OGERPON_HEARTHFLAME_MASK] = gMonIcon_OgerponHearthflameMask, TODO
    //[SPECIES_OGERPON_CORNERSTONE_MASK] = gMonIcon_OgerponCornerstoneMask, TODO
    [SPECIES_OGERPON_WELLSPRING_MASK] = gMonIcon_OgerponTealMask,
    [SPECIES_OGERPON_HEARTHFLAME_MASK] = gMonIcon_OgerponTealMask,
    [SPECIES_OGERPON_CORNERSTONE_MASK] = gMonIcon_OgerponTealMask,
    [SPECIES_OGERPON_TEAL_MASK_TERA] = gMonIcon_OgerponTealMask,
    //[SPECIES_OGERPON_WELLSPRING_MASK_TERA] = gMonIcon_OgerponWellspringMask, TODO
    //[SPECIES_OGERPON_HEARTHFLAME_MASK_TERA] = gMonIcon_OgerponHearthflameMask, TODO
    //[SPECIES_OGERPON_CORNERSTONE_MASK_TERA] = gMonIcon_OgerponCornerstoneMask, TODO
    [SPECIES_EGG] = gMonIcon_Egg,
};
*/

const struct SpritePalette gMonIconPaletteTable[] =
{
    { gMonIconPalettes[0], POKE_ICON_BASE_PAL_TAG + 0 },
    { gMonIconPalettes[1], POKE_ICON_BASE_PAL_TAG + 1 },
    { gMonIconPalettes[2], POKE_ICON_BASE_PAL_TAG + 2 },
    { gMonIconPalettes[3], POKE_ICON_BASE_PAL_TAG + 3 },
    { gMonIconPalettes[4], POKE_ICON_BASE_PAL_TAG + 4 },
    { gMonIconPalettes[5], POKE_ICON_BASE_PAL_TAG + 5 },
};

static const struct OamData sMonIconOamData =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
};

// fastest to slowest

static const union AnimCmd sAnim_0[] =
{
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(1, 6),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_1[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_2[] =
{
    ANIMCMD_FRAME(0, 14),
    ANIMCMD_FRAME(1, 14),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_3[] =
{
    ANIMCMD_FRAME(0, 22),
    ANIMCMD_FRAME(1, 22),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_4[] =
{
    ANIMCMD_FRAME(0, 29),
    ANIMCMD_FRAME(0, 29), // frame 0 is repeated
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sMonIconAnims[] =
{
    sAnim_0,
    sAnim_1,
    sAnim_2,
    sAnim_3,
    sAnim_4,
};

static const union AffineAnimCmd sAffineAnim_0[] =
{
    AFFINEANIMCMD_FRAME(0, 0, 0, 10),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_1[] =
{
    AFFINEANIMCMD_FRAME(-2, -2, 0, 122),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd *const sMonIconAffineAnims[] =
{
    sAffineAnim_0,
    sAffineAnim_1,
};

static const u16 sSpriteImageSizes[3][4] =
{
    [ST_OAM_SQUARE] =
    {
        [SPRITE_SIZE(8x8)]   =  8 * 8  / 2,
        [SPRITE_SIZE(16x16)] = 16 * 16 / 2,
        [SPRITE_SIZE(32x32)] = 32 * 32 / 2,
        [SPRITE_SIZE(64x64)] = 64 * 64 / 2,
    },
    [ST_OAM_H_RECTANGLE] =
    {
        [SPRITE_SIZE(16x8)]  = 16 * 8  / 2,
        [SPRITE_SIZE(32x8)]  = 32 * 8  / 2,
        [SPRITE_SIZE(32x16)] = 32 * 16 / 2,
        [SPRITE_SIZE(64x32)] = 64 * 32 / 2,
    },
    [ST_OAM_V_RECTANGLE] =
    {
        [SPRITE_SIZE(8x16)]  =  8 * 16 / 2,
        [SPRITE_SIZE(8x32)]  =  8 * 32 / 2,
        [SPRITE_SIZE(16x32)] = 16 * 32 / 2,
        [SPRITE_SIZE(32x64)] = 32 * 64 / 2,
    },
};

u8 CreateMonIcon(u16 species, void (*callback)(struct Sprite *), s16 x, s16 y, u8 subpriority, u32 personality, u8 gender)
{
    u8 spriteId;
    struct MonIconSpriteTemplate iconTemplate =
    {
        .oam = &sMonIconOamData,
        .image = GetMonIconPtr(species, personality, gender),
        .anims = sMonIconAnims,
        .affineAnims = sMonIconAffineAnims,
        .callback = callback,
        .paletteTag = POKE_ICON_BASE_PAL_TAG + gSpeciesInfo[species].iconPalIndex,
    };
    species = SanitizeSpeciesId(species);

    if (species > NUM_SPECIES)
        iconTemplate.paletteTag = POKE_ICON_BASE_PAL_TAG;
    else if (gSpeciesInfo[species].iconSpriteFemale != NULL && gender == MON_FEMALE)
        iconTemplate.paletteTag = POKE_ICON_BASE_PAL_TAG + gSpeciesInfo[species].iconPalIndexFemale;

    spriteId = CreateMonIconSprite(&iconTemplate, x, y, subpriority);

    UpdateMonIconFrame(&gSprites[spriteId]);

    return spriteId;
}


u8 CreateMonIconNoPersonality(u16 species, void (*callback)(struct Sprite *), s16 x, s16 y, u8 subpriority)
{
    u8 spriteId;
    struct MonIconSpriteTemplate iconTemplate =
    {
        .oam = &sMonIconOamData,
        .image = NULL,
        .anims = sMonIconAnims,
        .affineAnims = sMonIconAffineAnims,
        .callback = callback,
        .paletteTag = POKE_ICON_BASE_PAL_TAG + gSpeciesInfo[species].iconPalIndex,
    };

    iconTemplate.image = GetMonIconTiles(species, 0, GetGenderForSpecies(species, 0));
    spriteId = CreateMonIconSprite(&iconTemplate, x, y, subpriority);

    UpdateMonIconFrame(&gSprites[spriteId]);

    return spriteId;
}

//#define PAL_TAG_CUSTOM            0x1000
#define PAL_TAG_CUSTOM            (POKE_ICON_BASE_PAL_TAG)

u8 CreateMonIconCustomPaletteOffset(u16 species, void (*callback)(struct Sprite *), s16 x, s16 y, u8 subpriority, u16 paletteOffset)
{
    u8 spriteId;
    struct MonIconSpriteTemplate iconTemplate =
    {
        .oam = &sMonIconOamData,
        .image = NULL,
        .anims = sMonIconAnims,
        .affineAnims = sMonIconAffineAnims,
        .callback = callback,
        .paletteTag = PAL_TAG_CUSTOM + paletteOffset,
    };

    iconTemplate.image = GetMonIconTiles(species, TRUE, GetGenderForSpecies(species, 0));
    spriteId = CreateMonIconSprite(&iconTemplate, x, y, subpriority);

    UpdateMonIconFrame(&gSprites[spriteId]);

    return spriteId;
}

u8 CreateMissingMonIcon(void (*callback)(struct Sprite *), s16 x, s16 y, u8 subpriority, u16 paletteOffset)
{
    u8 spriteId;
    struct MonIconSpriteTemplate iconTemplate =
    {
        .oam = &sMonIconOamData,
        .image = NULL,
        .anims = sMonIconAnims,
        .affineAnims = sMonIconAffineAnims,
        .callback = callback,
        .paletteTag = PAL_TAG_CUSTOM + paletteOffset,
    };

    iconTemplate.image = gMonIcon_QuestionMark;
    spriteId = CreateMonIconSprite(&iconTemplate, x, y, subpriority);

    UpdateMonIconFrame(&gSprites[spriteId]);

    return spriteId;
}

u16 GetIconSpecies(u16 species, u32 personality)
{
    species = SanitizeSpeciesId(species);
    if (species == SPECIES_UNOWN)
        species = GetUnownSpeciesId(personality);
    return species;
}

u16 GetUnownLetterByPersonality(u32 personality)
{
    if (!personality)
        return 0;
    else
        return GET_UNOWN_LETTER(personality);
}

u16 GetIconSpeciesNoPersonality(u16 species)
{
    species = SanitizeSpeciesId(species);

    if (MailSpeciesToSpecies(species, &species) == SPECIES_UNOWN)
        return species += SPECIES_UNOWN_B; // TODO
    return GetIconSpecies(species, 0);
}

const u8 *GetMonIconPtr(u16 species, u32 personality, u8 gender)
{
    return GetMonIconTiles(GetIconSpecies(species, personality), personality, gender);
}

void FreeAndDestroyMonIconSprite(struct Sprite *sprite)
{
    FreeAndDestroyMonIconSprite_(sprite);
}

void LoadMonIconPalettes(void)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(gMonIconPaletteTable); i++)
        LoadSpritePalette(&gMonIconPaletteTable[i]);
}

// unused
void SafeLoadMonIconPalette(u16 species)
{
    u8 palIndex;
    palIndex = gSpeciesInfo[SanitizeSpeciesId(species)].iconPalIndex;
    if (IndexOfSpritePaletteTag(gMonIconPaletteTable[palIndex].tag) == 0xFF)
        LoadSpritePalette(&gMonIconPaletteTable[palIndex]);
}

void LoadMonIconPalette(u16 species)
{
    u8 palIndex = gSpeciesInfo[SanitizeSpeciesId(species)].iconPalIndex;
    if (IndexOfSpritePaletteTag(gMonIconPaletteTable[palIndex].tag) == 0xFF)
        LoadSpritePalette(&gMonIconPaletteTable[palIndex]);
}

void LoadMonIconPaletteGender(u16 species, u8 gender)
{
    u8 palIndex;
    species = SanitizeSpeciesId(species);
    if (gSpeciesInfo[species].iconSpriteFemale != NULL && gender == MON_FEMALE)
        palIndex = gSpeciesInfo[species].iconPalIndexFemale;
    else
        palIndex = gSpeciesInfo[species].iconPalIndex;
    if (IndexOfSpritePaletteTag(gMonIconPaletteTable[palIndex].tag) == 0xFF)
        LoadSpritePalette(&gMonIconPaletteTable[palIndex]);
}

void LoadMonIconPaletteCustomOffset(u16 species, u16 paletteOffset)
{
    u8 palIndex = gSpeciesInfo[SanitizeSpeciesId(species)].iconPalIndex;
    struct SpritePalette customIconPalette = { gMonIconPaletteTable[palIndex].data, PAL_TAG_CUSTOM + paletteOffset };

    if (IndexOfSpritePaletteTag(customIconPalette.tag) == 0xFF)
        LoadSpritePalette(&customIconPalette);
}

void FreeMonIconPalettes(void)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(gMonIconPaletteTable); i++)
        FreeSpritePaletteByTag(gMonIconPaletteTable[i].tag);
}

// unused
void SafeFreeMonIconPalette(u16 species)
{
    u8 palIndex;
    palIndex = gSpeciesInfo[SanitizeSpeciesId(species)].iconPalIndex;
    FreeSpritePaletteByTag(gMonIconPaletteTable[palIndex].tag);
}

void FreeMonIconPalette(u16 species)
{
    u8 palIndex;
    palIndex = gSpeciesInfo[SanitizeSpeciesId(species)].iconPalIndex;
    FreeSpritePaletteByTag(gMonIconPaletteTable[palIndex].tag);
}

void FreeMonIconPaletteCustomOffset(u16 species, u16 paletteOffset)
{
    u16 tag = PAL_TAG_CUSTOM + paletteOffset;
    FreeSpritePaletteByTag(tag);
}

void SpriteCB_MonIcon(struct Sprite *sprite)
{
    UpdateMonIconFrame(sprite);
}

const u8 *GetMonIconTiles(u16 species, u32 personality, u8 gender)
{
    const u8 *iconSprite;

    if (species > NUM_SPECIES)
        species = SPECIES_NONE;

    if (gSpeciesInfo[species].iconSpriteFemale != NULL && gender == MON_FEMALE)
        iconSprite = gSpeciesInfo[species].iconSpriteFemale;
    else if (gSpeciesInfo[species].iconSprite != NULL)
        iconSprite = gSpeciesInfo[species].iconSprite;
    else
        iconSprite = gSpeciesInfo[SPECIES_NONE].iconSprite;

    return iconSprite;
}

void TryLoadAllMonIconPalettesAtOffset(u16 offset)
{
    s32 i;
    if (offset <= BG_PLTT_ID(16 - ARRAY_COUNT(gMonIconPaletteTable)))
    {
        for (i = 0; i < (int)ARRAY_COUNT(gMonIconPaletteTable); i++)
        {
            LoadPalette(gMonIconPaletteTable[i].data, offset, PLTT_SIZE_4BPP);
            offset += 16;
        }
    }
}

u8 GetValidMonIconPalIndex(u16 species)
{
    return gSpeciesInfo[SanitizeSpeciesId(species)].iconPalIndex;
}

u8 GetMonIconPaletteIndexFromSpecies(u16 species)
{
    return gSpeciesInfo[SanitizeSpeciesId(species)].iconPalIndex;
}

const u16 *GetValidMonIconPalettePtr(u16 species)
{
    return gMonIconPaletteTable[gSpeciesInfo[SanitizeSpeciesId(species)].iconPalIndex].data;
}

u8 UpdateMonIconFrame(struct Sprite *sprite)
{
    u8 result = 0;

    if (sprite->animDelayCounter == 0)
    {
        s16 frame = sprite->anims[sprite->animNum][sprite->animCmdIndex].frame.imageValue;

        switch (frame)
        {
        case -1:
            break;
        case -2:
            sprite->animCmdIndex = 0;
            break;
        default:
            RequestSpriteCopy(
                // pointer arithmetic is needed to get the correct pointer to perform the sprite copy on.
                // because sprite->images is a struct def, it has to be casted to (u8 *) before any
                // arithmetic can be performed.
                (u8 *)sprite->images + (sSpriteImageSizes[sprite->oam.shape][sprite->oam.size] * frame),
                (u8 *)(OBJ_VRAM0 + sprite->oam.tileNum * TILE_SIZE_4BPP),
                sSpriteImageSizes[sprite->oam.shape][sprite->oam.size]);
            sprite->animDelayCounter = sprite->anims[sprite->animNum][sprite->animCmdIndex].frame.duration & 0xFF;
            sprite->animCmdIndex++;
            result = sprite->animCmdIndex;
            break;
        }
    }
    else
    {
        sprite->animDelayCounter--;
    }
    return result;
}

static u8 CreateMonIconSprite(struct MonIconSpriteTemplate *iconTemplate, s16 x, s16 y, u8 subpriority)
{
    u8 spriteId;

    struct SpriteFrameImage image = { NULL, sSpriteImageSizes[iconTemplate->oam->shape][iconTemplate->oam->size] };

    struct SpriteTemplate spriteTemplate =
    {
        .tileTag = TAG_NONE,
        .paletteTag = iconTemplate->paletteTag,
        .oam = iconTemplate->oam,
        .anims = iconTemplate->anims,
        .images = &image,
        .affineAnims = iconTemplate->affineAnims,
        .callback = iconTemplate->callback,
    };

    spriteId = CreateSprite(&spriteTemplate, x, y, subpriority);
    gSprites[spriteId].animPaused = TRUE;
    gSprites[spriteId].animBeginning = FALSE;
    gSprites[spriteId].images = (const struct SpriteFrameImage *)iconTemplate->image;
    return spriteId;
}

static void FreeAndDestroyMonIconSprite_(struct Sprite *sprite)
{
    struct SpriteFrameImage image = { NULL, sSpriteImageSizes[sprite->oam.shape][sprite->oam.size] };
    sprite->images = &image;
    DestroySprite(sprite);
}

void SetPartyHPBarSprite(struct Sprite *sprite, u8 animNum)
{
    sprite->animNum = animNum;
    sprite->animDelayCounter = 0;
    sprite->animCmdIndex = 0;
}
