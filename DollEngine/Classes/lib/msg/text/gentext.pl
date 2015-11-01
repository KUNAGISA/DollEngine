
# メッセージ類のヘッダーファイルなどを生成します。
use utf8;
use warnings;
use strict;

{
	my @message_files = ("Messages_TJS2.csv","Messages_Public.csv","Messages_Win32.csv","Messages_Qt.csv");

	my $jp_res_filename = 'string_table_jp.h';
	my $en_res_filename = 'string_table_en.h';
	my $res_header_filename = 'string_table_resource.h';
	my $tjs_error_header = 'tjsErrorInc.h';
	my $tvp_mes_load = 'MsgLoad.cpp';

	my @mes_id;
	my @res_id;
	my @mes_jp;
	my @mes_en;


	my $Messages_size = @message_files;
	for (my $i = 0; $i < $Messages_size; $i++) {
		my $message_file = $message_files[$i];

		open CsvFile, "$message_file" or die;

		<CsvFile>;
		my @worksheet;
		my $linenumber = 0;
		while($_=<CsvFile>)
		{
			my @line=split /;/,$_;
			# foreach my $k (@line) {
			# 	print "$k\n";
			# }
			push @worksheet,[@line];
			$linenumber ++;
		}
		close CsvFile;

		my $MesId;
		my $row = 0;
		for (my $k = 0; $k < $linenumber; $k++) 
		{
			my $MesId = $worksheet[$k]->[0];
			my $MesJp = $worksheet[$k]->[1];
			my $MesEn = $worksheet[$k]->[2];
			my $MesOpt = $worksheet[$k]->[3];
			# print $MesId."\n";
			# print $MesJp."\n";
			# print $MesEn."\n";
			# print "\n";

			$MesJp =~ s/(\\")/\"/g;
			$MesJp =~ s/(\\')/\'/g;
			$MesJp =~ s/(\")/\\\"/g;
			$MesJp =~ s/(\')/\\\'/g;

			$MesEn =~ s/(\\")/\"/g;
			$MesEn =~ s/(\\')/\'/g;
			$MesEn =~ s/(\")/\\\"/g;
			$MesEn =~ s/(\')/\\\'/g;

			# $MesOpt =~ s/\n//g;

			# $MesEn =~ s/(\\")/""/g;
			# $MesEn =~ s/(\\')/'/g;

			my $ResId = $MesId;
			$ResId =~ s/^(TVP)/$1_/;
			$ResId =~ s/^(TJS)/$1_/;
			$ResId =~ s/([a-z])([A-Z])/$1_$2/g;
			$ResId = uc $ResId;
			if( defined $MesOpt ) {
				$MesOpt =~ s/(\n)//g;
				# $MesOpt =~ s/( )//g;
				$ResId .= "_".$MesOpt;
			}
			$ResId = "IDS_".$ResId;
			push @mes_id, $MesId;
			push @res_id, $ResId;
			push @mes_jp, $MesJp;
			push @mes_en, $MesEn;
			$row ++;
		}
	}

	# String Table のリソースを出力
	open FHJP, ">$jp_res_filename" or die;
	open FHEN, ">$en_res_filename" or die;
	open FHH, ">$res_header_filename" or die;

	open FHEH, ">$tjs_error_header" or die;
	open FHCPP, ">$tvp_mes_load" or die;

	print FHJP <<'HEADER';
// generated from gentext.pl Messages.xlsx
#ifndef __STRING_TABLE_JP_H__
#define __STRING_TABLE_JP_H__
HEADER

	print FHEN <<'HEADER';
// generated from gentext.pl Messages.xlsx
#ifndef __STRING_TABLE_EN_H__
#define __STRING_TABLE_EN_H__
HEADER

	print FHH  <<'HEADER';
// generated from gentext.pl Messages.xlsx
#ifndef __STRING_TABLE_RESOURCE_H__
#define __STRING_TABLE_RESOURCE_H__

#ifndef __DEBUG_LANGUAGE_

#include "string_table_en.h"

#else

#if __DEBUG_LANGUAGE_ == __DEBUG_LANGUAGE_EN
#include "string_table_en.h"
#elif __DEBUG_LANGUAGE_ == __DEBUG_LANGUAGE_JP
#include "string_table_jp.h"
#elif __DEBUG_LANGUAGE_ == __DEBUG_LANGUAGE_CH
#include "string_table_ch.h"
#endif

#endif

HEADER

	print FHEH  <<'HEADER';
// generated from gentext.pl Messages.xlsx
#ifndef __TJS_ERROR_INC_H__
#define __TJS_ERROR_INC_H__
#ifndef TJS_MSG_DECL
	#define TJS_MSG_DECL(name, msg) extern tTJSMessageHolder name;
	#define TJS_MSG_DECL_NULL(name) extern tTJSMessageHolder name;
#endif
extern void TVPLoadMessage();
HEADER

	print FHCPP <<'CPPSRC';
// generated from gentext.pl Messages.xlsx
#include "tjsCommHead.h"
#include "tjsError.h"
#include "string_table_resource.h"

static bool IS_LOAD_MESSAGE = false;
CPPSRC

	my $length = @mes_id;
	my $maxlen = 24;
	my $mesmaxlen = 1024;
	for( my $i = 0; $i < $length; $i++ ) {
		my $len = length $res_id[$i];
		if( ($len+1) > $maxlen ) { $maxlen = ($len+1); }
		$len = length $mes_jp[$i];
		if( ($len+1) > $mesmaxlen ) { $mesmaxlen = ($len+1); }
		$len = length $mes_en[$i];
		if( ($len+1) > $mesmaxlen ) { $mesmaxlen = ($len+1); }
	}
	print FHCPP "static const int MAX_MESSAGE_LENGTH = $mesmaxlen;\n";
	print FHCPP "enum {\n";

	for( my $i = 0; $i < $length; $i++ ) {
		my $len = length $res_id[$i];
		my $line = "#define ".$res_id[$i];
		$line =~ s/\n//g;
		my $header_res = "#define ".$res_id[$i];
		for( my $j = $len; $j < $maxlen; $j++ ) {
			$line .= " ";
			$header_res .= " ";
		}
		my $jpline = $line . "L\"".$mes_jp[$i]."\"\n";
		my $enline = $line . "L\"".$mes_en[$i]."\"\n";
		# $jpline =~ s/\n/\\n/g;
		# $jpline =~ s/\"\"/\"\\\"/g;

		print FHJP $jpline;
		print FHEN $enline;
		my $id = $i + 10000; # 10000以降の番号に割り当てておく
		# print FHH $header_res.$id."\n"
		print FHEH "TJS_MSG_DECL_NULL(".$mes_id[$i].")\n";
		my $enumid = $res_id[$i];
		$enumid =~ s/^(IDS_)//;
		$enumid = "NUM_".$enumid;
		print FHCPP "\t".$enumid.",\n";
	}
	print FHCPP "\tNUM_MESSAGE_MAX\n";
	print FHCPP "};\n";
	print FHCPP "const tjs_char* RESOURCE_MESSAGE[NUM_MESSAGE_MAX] = {\n";
	for( my $i = 0; $i < $length; $i++ ) {
		print FHCPP "\t".$res_id[$i].",\n";
	}
	print FHCPP <<'CPPSRC';
};

namespace TJS {

void TVPLoadMessage() {
	if( IS_LOAD_MESSAGE ) return;
	IS_LOAD_MESSAGE = true;
CPPSRC
	my $is_opt = 0;
	for( my $i = 0; $i < $length; $i++ ) {
		my $enumid = $res_id[$i];
		$enumid =~ s/^(IDS_)//;
		$enumid = "NUM_".$enumid;
		# if( defined $mes_opt[$i] ) {
		# 	if( $mes_opt[$i] eq "CRLF" ) {
		# 		print FHCPP "#ifdef TJS_TEXT_OUT_CRLF\n";
		# 		print FHCPP "\t".$mes_id[$i].".AssignMessage( RESOURCE_MESSAGE[".$enumid."] );\n";
		# 		print FHCPP "#else\n";
		# 		$is_opt = 1;
		# 	} elsif( $mes_opt[$i] eq "ANSI" ) {
		# 		print FHCPP "#ifdef TVP_TEXT_READ_ANSI_MBCS\n";
		# 		print FHCPP "\t".$mes_id[$i].".AssignMessage( RESOURCE_MESSAGE[".$enumid."] );\n";
		# 		print FHCPP "#else\n";
		# 		$is_opt = 1;
		# 	}
		# } else {
			print FHCPP "\t".$mes_id[$i].".AssignMessage( RESOURCE_MESSAGE[".$enumid."] );\n";
			if( $is_opt == 1 ) {
				print FHCPP "#endif\n";
				$is_opt = 0;
			}
		# }
	}
	print FHCPP <<'CPPSRC';
}
const tjs_char* TVPGetMessage( tjs_int id ) {
	if( id >= 0 && id < NUM_MESSAGE_MAX ) {
		return RESOURCE_MESSAGE[id];
	} else {
		return NULL;
	}
}
static void TVPFreeMessages() {
	for( int i = 0; i < NUM_MESSAGE_MAX; i++ ) {
		delete[] RESOURCE_MESSAGE[i];
	}
    IS_LOAD_MESSAGE = false;
}

}

CPPSRC

	close FHCPP;

	print FHJP "#endif\n";
	close FHJP;

	print FHEN "#endif\n";
	close FHEN;

	print FHH "#endif\n";
	close FHH;

	print FHEH "#endif\n";
	close FHEH;



	exit;
}



