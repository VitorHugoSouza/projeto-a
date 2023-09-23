import { Box, Link, Typography } from "@mui/material";

export default function Footer() {
  return(
  <>
    <Box sx={{ bgcolor: 'background.paper', p: 6 }} component="footer">
      <Typography variant="body2" color="text.secondary" align="center">
        {'Gustavo Mazzuco e Vitor Hugo de Souza - UNISATC '}
        {new Date().getFullYear()}
        {'.'}
      </Typography>
      </Box>
  </>
  );
}